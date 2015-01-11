<?php
  
//proximate to v2_profiles_whiteboard_add, changed to accommodate service call

function cmwn_oauth_services_whiteboard_add($uid) {

		set_time_limit(0);


		$extensions = array('image'=>array('gif','jpg','JPG','jpeg','png'),'video'=>array('avi','flv','m4v','mov','mp4','mpg','wmv'));
		$images = array();
		$videos = array();
		$is_file = false;

		if (sizeof($_FILES) > 0) {
			foreach ($_FILES['files']['name'] as $key => $value) {
				if (!empty($value)) {
					if (!$file = file_save_upload($key,array(),file_directory_path(),FILE_EXISTS_RENAME)) {
						return array('success' => false, 'msg'=>('Your file could not be uploaded.'));
					}
					$path = pathinfo($value);
					if (in_array($path['extension'],$extensions['image'])) {
						$images[] = $file;
						$is_file = true;
					} elseif (in_array($path['extension'],$extensions['video'])) {
						$videos[] = $file;
						$is_file = true;
					}
				}
			}
		}

		$video_reference = 0;

		if (sizeof($videos) > 0) {
			$node = new stdClass();
			$node->body = $content;
			$node->field_user_reference[]['uid'] = $uid;
			foreach ($videos as $video) {
				$node->field_video[] = array(
					'fid'=>$video->fid,
					'filemime'=>$video->filemime,
					'filename'=>$video->filename,
					'filepath'=>$video->filepath,
					'filesize'=>$video->filesize,
					'list'=>1,
					'uid'=>$video->uid,
				);
				$viddler = _cmwn_video_upload_video(realpath('./'.$video->filepath),$video->filename,$video->filename,variable_get('cmwn_video_viddler_api_key',''),variable_get('cmwn_video_viddler_user',''),variable_get('cmwn_video_viddler_pass',''));
				if (isset($viddler['video']) && is_array($viddler['video'])) {
					$node->field_viddler_id[0]['value'] = $viddler['video']['id'];
					$node->field_viddler_permalink[0]['value'] = $viddler['video']['url'];
					$node->field_viddler_thumbnail[0]['value'] = $viddler['video']['thumbnail_url'];
				}
			}
			$node->status = 0;
			$node->title = $video->filename;
			$node->type = 'video';
  		$node->uid = $uid;
			node_validate($node);
			node_submit($node);
			node_save($node);
			$video_reference = $node->nid;
			$is_file = true;
		}

		$content = isset($_POST['content'])? $_POST['content'] : '';
		if (empty($content) && !$is_file) {
      return array('success' => false, 'msg'=>t('Please include a message with this post.'));
		}



		$node = new stdClass();
		$node->body = $content;
		$node->comments = 2;
		foreach ($images as $image) {
			$node->field_image[] = array(
				'fid'=>$image->fid,
				'filemime'=>$image->filemime,
				'filename'=>$image->filename,
				'filepath'=>$image->filepath,
				'filesize'=>$image->filesize,
				'list'=>1,
				'uid'=>$image->uid,
			);
		}
		$node->field_user_reference[]['uid'] = $uid;
		if ($video_reference > 0) {
			$node->field_video_reference[]['nid'] = $video_reference;
		}
		$node->status = 0;
		$node->title = 'Whiteboard ' . time();
		$node->type = 'whiteboard';
		$node->uid = $uid;
		node_validate($node);
		node_submit($node);
		node_save($node);
    return array('success' => true, 'node' => $node);
}