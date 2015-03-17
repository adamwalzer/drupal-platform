<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/whiteboard"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_whiteboard_index",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/%/comments/%/delete"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1,3,5),
		"page callback" => "v2_profiles_whiteboard_comments_delete",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/%/comments/%/report"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1,3,5),
		"page callback" => "v2_profiles_whiteboard_comments_report",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/%/comments/add"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_whiteboard_comments_add",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/%/delete"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_whiteboard_delete",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/%/report"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_whiteboard_report",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/whiteboard/add"] = array(	
		"access arguments" => array("access content"),
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_whiteboard_add",
		"title" => "Whiteboard",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_whiteboard_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/whiteboard/index'
	);

	///

	function v2_profiles_whiteboard_index($uid) {
    
		$data = new stdClass();

		$user = user_load($uid);

		$items = v2_profiles_whiteboard_query($uid);

		$data->items = $items;
		$data->user = $user;

		return theme('v2_profiles_whiteboard_index', $data);

	}

	function v2_profiles_whiteboard_add($uid) {

		set_time_limit(0);

		global $user;

		$extensions = array('image'=>array('gif','jpg','JPG','jpeg','png'),'video'=>array('avi','flv','m4v','mov','mp4','mpg','wmv'));
		$images = array();
		$videos = array();
		$is_file = false;

		if (sizeof($_FILES) > 0) {
			foreach ($_FILES['files']['name'] as $key => $value) {
				if (!empty($value)) {
					if (!$file = file_save_upload($key,array(),file_directory_path(),FILE_EXISTS_RENAME)) {
						drupal_set_message('Your file could not be uploaded.','error');
						drupal_goto('user');
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
			$node->field_user_reference[]['uid'] = $user->uid;
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
			drupal_set_message('Please enter a message before posting.','error');
			drupal_goto('user');
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
		$node->field_user_reference[]['uid'] = $user->uid;
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
    $tid_feed_type = false;
		if ($user->uid == $uid) {
			$excerpt = '<a href="/user/' . $user->uid . '">' . $user->name . '</a> posted on his/her whiteboard.';
			$tid_feed_type = 90;
		} else {
			$friend = user_load($uid);
			$excerpt = '<a href="/user/' . $user->uid . '">' . $user->name . '</a> posted on <a href="/user/' . $friend->uid . '">' . $friend->name . '\'s</a> whiteboard.';
			$tid_feed_type = 91;			
		}

		v2_profiles_feed_insert(
			$user->uid,
			88,
			$tid_feed_type,
			'Feed ' . time(),
			'',
			$excerpt
		);

		$_SESSION['show_post_pending_moderation'] = true;

		if ($user->uid == $uid) {
			drupal_goto('user/'.$uid);
		} else {
			drupal_goto('user/'.$user->uid.'/friends/'.$uid);
		}

	}

	function v2_profiles_whiteboard_comments_add($uid,$nid) {

		global $user;

		$content = isset($_POST['content'])? $_POST['content'] : '';

		if (empty($content)) {
			drupal_set_message('Please enter a message before posting.','error');
			drupal_goto('user');
		}

		$query = "

			INSERT INTO `comments` (
				`pid`,
				`nid`,
				`uid`,
				`subject`,
				`comment`,
				`hostname`,
				`timestamp`,
				`status`,
				`format`,
				`thread`
			) VALUES (
				'0',
				" . $nid . ",
				" . $user->uid . ",
				'Comment " . time() . "',
				'" . db_escape_string($content) . "',
				'" . $_SERVER['REMOTE_ADDRESS'] . "',
				'" . time() . "',
				'1',
				'1',
				'01/'
			);

		";

		db_query($query);

		if ($user->uid == $uid) {
			$excerpt = '<a href="/user/' . $user->uid . '">' . $user->name . '</a> replied to their post.';
			$tid_feed_type = 92;
		} else {
			$friend = user_load($uid);
			$excerpt = '<a href="/user/' . $user->uid . '">' . $user->name . '</a> replied to <a href="/user/' . $friend->uid . '">' . $friend->name . '\'s</a> post.';
			$tid_feed_type = 93;			
		}

		v2_profiles_feed_insert(
			$user->uid,
			88,
			$tid_feed_type,
			'Feed ' . time(),
			'',
			$excerpt
		);

		$_SESSION['show_post_pending_moderation'] = true;

		if ($user->uid == $uid) {
			drupal_goto('user/'.$uid);
		} else {
			drupal_goto('user/'.$user->uid.'/friends/'.$uid);
		}

	}

	function v2_profiles_whiteboard_comments_delete($uid,$nid,$cid) {

		global $user;

		$nid = intval($nid);
		$cid = intval($cid);

		$query = "
			DELETE FROM
				`comments`
			WHERE
				`cid` = " . $cid . " AND
				`nid` = " . $nid . ";
		";

		db_query($query);

		drupal_get_messages();

		if ($user->uid == $uid) {
			drupal_goto('user/'.$uid);
		} else {
			drupal_goto('user/'.$user->uid.'/friends/'.$uid);
		}

	}

	function v2_profiles_whiteboard_comments_report($uid,$nid,$cid) {

		global $user;

		$nid = intval($nid);
		$cid = intval($cid);

		global $user;

		$nid = intval($nid);

		if ($user->uid == $uid) {
			$destination = 'user/'.$uid;
		} else {
			$destination = 'user/'.$user->uid.'/friends/'.$uid;
		}

		$uri = '/flag/flag/flag_as_inappropriate_comment/'.$cid.'?destination='.urlencode($destination).'&token='.drupal_get_token($cid);

		header('Location: ' . $uri);

		exit();

	}

	function v2_profiles_whiteboard_delete($uid,$nid) {

		global $user;

		$nid = intval($nid);

		$tmp = $user;

		$user = user_load(1);
		node_delete($nid);

		$user = $tmp;

		drupal_get_messages();

		if ($user->uid == $uid) {
			drupal_goto('user/'.$uid);
		} else {
			drupal_goto('user/'.$user->uid.'/friends/'.$uid);
		}

	}

	function v2_profiles_whiteboard_report($uid,$nid) {

		global $user;

		$nid = intval($nid);

		if ($user->uid == $uid) {
			$destination = 'user/'.$uid;
		} else {
			$destination = 'user/'.$user->uid.'/friends/'.$uid;
		}

		$uri = '/flag/flag/flag_as_inappropriate/'.$nid.'?destination='.urlencode($destination).'&token='.drupal_get_token($nid);

		header('Location: ' . $uri);

		exit();

	}

	function v2_profiles_whiteboard_query($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$query = "
			SELECT
				`n`.`nid`
			FROM
				`node` AS `n`
			WHERE
				`n`.`type` = 'whiteboard' AND
				`n`.`uid` = " . $uid . "
			ORDER BY
				`n`.`created` DESC;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$node = node_load($result->nid);
      $users = array();			
			$item = new stdClass();
			$item->nid = $node->nid;
			$item->comments = v2_profiles_whiteboard_query_comments($node->nid);
			$item->content = $node->body;
			$item->id = $node->nid;
			$item->image = $node->field_image[0]['filepath'];
			$item->status = $node->status;
			$item->user = user_load($node->field_user_reference[0]['uid']);
			$item->video = node_load($node->field_video_reference[0]['nid']);
			
			//pull flag content
      $flag = flag_get_flag('like');
      $flag_count = $flag->get_count($item->nid);
      $flagmsg = t('Be the first to like this post!');    
       
      $flaggers = db_query('SELECT u.uid, u.name FROM {flag_content} fc join {users} u on u.uid = fc.uid where content_type ="node" and content_id = %d and fid = %d order by timestamp desc', array($item->nid, 12));
      while($flagger = db_fetch_array($flaggers)){
        $users[] = l($flagger['name'],'user/' . $uid . '/friends/' . $flagger['uid']);
      }
       
      switch (true){
        case $flag_count <= 3 && $flag_count > 0:
          $flagmsg = implode(', ',$users) . ' <em> liked this</em>';
          break;
        case 0:
        case $flag_count == null || $flag_count == false:
          break;
        default: //more than three
          $flagmsg = implode(', ', (array_slice($users, 0, 3))) . ' and <em class="modal-tip" id="modal-tip-'.$node->nid.'">'. theme('item_list',array_slice($users,-2), null,'ul',array('class' => 'morelikes'), 'morelikes-' . $node->nid,'item-list-likes') . ($flag_count-3) . ' others liked this</em>';        
          break;
      }
        
      $item->flags_output = flag_create_link('like', $item->nid) . '<span>&nbsp;&middot;&nbsp;' . $flagmsg. '</span>';
			
			$items[] = $item;
		}

		return $items;

	}

	function v2_profiles_whiteboard_query_comments($nid) {

		$items = array();

		$node = node_load($nid);

		if (!$node) return $items;

		$query = "
			SELECT
				`c`.`cid` AS `cid`,
				`c`.`uid` AS `uid`,
				`c`.`comment` AS `content`,
				`c`.`status` AS `status`
			FROM
				`comments` AS `c`
			WHERE
				`c`.`nid` = " . $nid . "
			ORDER BY
				`c`.`timestamp` ASC;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$item = new stdClass();
			$item->content = $result->content;
			$item->id = $result->cid;
			$item->user = user_load($result->uid);
			$item->status = ($result->status == 0)?1:0;
			$items[] = $item;
		}

		return $items;

	}

?>