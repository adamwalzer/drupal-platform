<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/%/avatars'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_avatars_index',
		'title' => 'avatars',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/avatars/add'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_avatars_add',
		'title' => 'avatars',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/avatars/browse'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_avatars_browse',
		'title' => 'avatars',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/avatars/browse/add'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_avatars_browse_add',
		'title' => 'avatars',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_avatars_add'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/avatars/add'
	);

	$v2_profiles_theme_items['v2_profiles_avatars_browse'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/avatars/browse'
	);

	$v2_profiles_theme_items['v2_profiles_avatars_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/avatars/index'
	);

	function v2_profiles_avatars_add($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$extensions = array('image'=>array('gif','jpg','JPG','jpeg','png'));
		$images = array();

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
					}
				}
			}
		}

		if (sizeof($images) > 0) {

			$node = new stdClass();
			$node->body = '';
			foreach ($images as $image) {
				$node->field_custom_avatar[] = array(
					'fid'=>$image->fid,
					'filemime'=>$image->filemime,
					'filename'=>$image->filename,
					'filepath'=>$image->filepath,
					'filesize'=>$image->filesize,
					'list'=>1,
					'uid'=>$image->uid,
				);
			}
			$node->status = 0;
			$node->title = $image->filename;
			$node->type = 'custom_avatar';
			$node->uid = $user->uid;
			node_validate($node);
			node_submit($node);
			node_save($node);

			drupal_set_message('Your avatar has been updated.');

			$_SESSION['avatar_updated_pending_moderation'] = 1;

			drupal_goto('user');

		}

		return theme('v2_profiles_avatars_add', $data);

	}

	function v2_profiles_avatars_browse($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$items = v2_profiles_avatars_query_all($user->uid);

		$data->user = $user;
		$data->items = $items;

		return theme('v2_profiles_avatars_browse', $data);

	}

	function v2_profiles_avatars_browse_add($uid) {

		if (sizeof($_POST) > 0) {

			$_user = user_load($uid);
			$_nid = isset($_POST['nid'])? $_POST['nid'] : 0;

			if (!empty($_user->picture)) {
				try {
					unlink($_user->picture);
				} catch(Exception $e) {

				}
			}

			user_save($_user, array('picture'=>''));

			$_node = GenericUser::castAs($_user)->getBaseProfile();

			$_node->field_avatar_reference[0]['nid'] = $_nid;

			node_save($_node);

			drupal_set_message('Your avatar has been updated.');

		}

		drupal_goto('user');

	}

	function v2_profiles_avatars_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$avatar = v2_profiles_avatars_query($user->uid);

		$data->user = $user;
		$data->user->avatar = $avatar;

		return theme('v2_profiles_avatars_index', $data);

	}

	function v2_profiles_avatars_query($uid) {
		global $user;
		
		$value = '';

		$cur_user = user_load($uid);

		if (!$cur_user) return $value;

		$query = "
			SELECT
				`f`.`filepath`
			FROM
				`node` AS `n` JOIN
				`content_type_custom_avatar` AS `ctca` ON `n`.`nid` = `ctca`.`nid` JOIN
				`files` AS `f` ON `ctca`.`field_custom_avatar_fid` = `f`.`fid`
			WHERE
				`n`.`uid` = " . $cur_user->uid . "
				".($user->uid!=$uid?" AND `n`.`status` = 1":"")."
			ORDER BY
				`n`.`nid` DESC
			LIMIT
				1
		";

		$value = db_result(db_query($query));

		/*
		if (empty($value)) {
			$query = "
				SELECT
					`u`.`picture` AS `avatar`
				FROM
					`users` AS `u`
				WHERE
					`u`.`uid` = " . $user->uid . " AND
					`u`.`status` = 1;
			";
			$value = db_result(db_query($query));
		}
		*/

		if (empty($value)) {
			$node = GenericUser::castAs($user)->getBaseProfile();
			if ($node) {
				$node = node_load($node->field_avatar_reference[0]['nid']);
				if ($node) {
					$value = $node->field_avatar[0]['filepath'];
				}
			}
		}

		return (!empty($value))? '/'.imagecache_create_path('216x216', $value) : '/sites/all/themes/cmwn/assets/img/default/avatars/216.png';

	}

	function v2_profiles_avatars_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$query = "
			SELECT
				`n`.`nid` AS `nid`,
				`f`.`filepath` AS `path`
			FROM
				`node` AS `n` JOIN
				`content_type_avatar` AS `cta` ON `n`.`nid` = `cta`.`nid` JOIN
				`files` AS `f` ON `cta`.`field_avatar_fid` = `f`.`fid`
				
			WHERE
				`n`.`status` = 1 AND
				`n`.`type` = 'avatar' AND
				`cta`.`field_avatar_type_value` = '" . db_escape_string($user->user_type) . "';
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$item = new stdClass();
			$item->nid = $result->nid;
			$item->src = '/'.$result->path;
			$items[] = $item;
		}

		return $items;

	}