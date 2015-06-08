<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/%/children'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_children_index',
		'title' => 'Children',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/children/%'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1, 3),
		'page callback' => 'v2_profiles_children_read',
		'title' => 'Children',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/children/%/delete'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1, 3),
		'page callback' => 'v2_profiles_children_delete',
		'title' => 'Children',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/children/add'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_children_add',
		'title' => 'Children',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_menu_items['user/%/children/permissions'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_children_permissions',
		'title' => 'Children',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_children_add'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/children/add'
	);

	$v2_profiles_theme_items['v2_profiles_children_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/children/index'
	);

	$v2_profiles_theme_items['v2_profiles_children_permissions'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/children/permissions'
	);

	$v2_profiles_theme_items['v2_profiles_children_read'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/children/read'
	);

	function v2_profiles_children_add($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		if (sizeof($_POST) > 0) {

			$_token = isset($_POST['token'])? $_POST['token'] : '';

			$parent = ParentUser::castAs(user_load($user->uid));
			$token = get_parent_registration_token($_token);
			if ($token) {
				$child = user_load($token['cuid']);
				if ($child) {
					$child = ChildUser::castAs($child);
					if ($child) {
						$token['puid'] = $parent->uid;
						$token['puip'] = ip2long($_SERVER['REMOTE_ADDR']);
						drupal_write_record('cmwn_parental_consent_token', $token, array('cuid'));
						user_relationships_request_relationship($parent, $child, 2, true);
						user_relationships_request_relationship($child, $parent, 3, true);
						$roles = user_roles();
						$index = variable_get('cmwn_module_approved_child_role', '');
						if ($index) {
							$child->roles[$index] = $roles[$index];
							user_save($child, array('roles' => $child->roles));
						}
						drupal_set_message($child->name.' has been linked to your account.');
						drupal_goto('user/' . $user->uid . '/children/permissions');
					}
				}
			}

			drupal_set_message('Unable to link child to your account.', 'error');
			drupal_goto('user/' . $user->uid . '/children/add');

		}

		$data->user = $user;

		return theme('v2_profiles_children_add', $data);

	}

	function v2_profiles_children_link_imported($puid, $cuid) {
		$data = new stdClass();
		$user = user_load($puid);//parent $uid

		$parent = ParentUser::castAs(user_load($user->uid));
			$child = user_load($cuid);
			if ($child) {
				$child = ChildUser::castAs($child);
				if ($child) {
					user_relationships_request_relationship($parent, $child, 2, true);
					user_relationships_request_relationship($child, $parent, 3, true);
					$roles = user_roles();
					$index = variable_get('cmwn_module_approved_child_role', '');
					if ($index) {
						$child->roles[$index] = $roles[$index];
						user_save($child, array('roles' => $child->roles));
					}
				}

		}
	}

	function v2_profiles_children_delete($uid1, $uid2) {

		user_delete(array(), $uid2);

		drupal_set_message('Your child\'s profile was successfully deleted.');

		drupal_goto('user/' . $uid1 . '/children');

	}

	function v2_profiles_children_index($uid) {

		$data = new stdClass();

		$items = v2_profiles_children_query_all($uid);

		$data->items = $items;
		$data->teaser = true;

		return theme('v2_profiles_children_index', $data);

	}

	function v2_profiles_children_permissions($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$items = v2_profiles_children_query_all($user->uid);

		$roles = array(
			27 => 'can_upload_media',
			28 => 'can_make_friends',
			29 => 'can_receive_notices',
			30 => 'can_upload_flip_media',
			31 => 'can_receive_notices_via_parent',
		);

		if (sizeof($_POST) > 0) {

			$_uid = $_POST['uid']? intval($_POST['uid']) : 0;

			$_roles = array(
				27 => ($_POST['can_upload_media'] == 1)? true : false,
				28 => ($_POST['can_make_friends'] == 1)? true : false,
				29 => ($_POST['can_receive_notices'] == 1)? true : false,
				30 => ($_POST['can_upload_media'] == 2)? true : false,
				31 => ($_POST['can_receive_notices'] == 2)? true : false,
			);

			$_user = user_load($_uid);

			foreach ($roles as $key => $value) {
				unset($_user->roles[$key]);
			}

			foreach ($_roles as $key => $value) {
				if ($value) {
					$_user->roles[$key] = $roles[$key];
				}
			}

			user_save($_user, array('roles'=>$_user->roles));

			drupal_set_message('Your child\'s permissions have been updated.');

			drupal_goto('user/' . $user->uid . '/children/permissions');

		}

		$data->user = $user;
		$data->items = $items;
		$data->roles = $roles;

		return theme('v2_profiles_children_permissions', $data);

	}

	function v2_profiles_children_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$query = "
			SELECT
				`u`.`uid`,
				`u`.`name`
			FROM
				`user_relationships` AS `ur` JOIN `users` AS `u` ON `ur`.`requestee_id` = `u`.`uid`
			WHERE
				`ur`.`requester_id` = " . $user->uid . " AND
				`ur`.`rtid` = 2 AND
				`ur`.`approved` = 1;
		";

		$results = db_query($query,$uid);

		while ($result = db_fetch_object($results)) {
			$item = new stdClass();
			$item->href = '/user/' . $user->uid . '/children/' . $result->uid;
			$item->name = $result->name;
			$item->roles = user_load($result->uid)->roles;
			$item->src = v2_profiles_avatars_query($result->uid);
			$item->uid = $result->uid;
			$items[] = $item;
		}

		return $items;

	}

	function v2_profiles_children_read($uid1,$uid2) {

		$data = new stdClass();

		$items = v2_profiles_children_query_all($uid1);

		foreach ($items as $key => $value) {
			if ($value->uid != $uid2) {
				unset($items[$key]);
			}
		}

		$data->items = $items;
		$data->teaser = false;

		return theme('v2_profiles_children_read', $data);

	}
