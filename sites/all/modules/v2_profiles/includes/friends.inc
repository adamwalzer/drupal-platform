<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/friends"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_friends_index",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/%"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_friends_read",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/%/add"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_friends_add",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/%/approve"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_friends_approve",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/%/ignore"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_friends_ignore",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/%/remove"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_friends_remove",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/browse"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_friends_browse",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/friends/search"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_friends_search",
		"title" => "Friends",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_friends_browse'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/friends/browse'
	);

	$v2_profiles_theme_items['v2_profiles_friends_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/friends/index'
	);

	$v2_profiles_theme_items['v2_profiles_friends_read'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/friends/read'
	);

	$v2_profiles_theme_items['v2_profiles_friends_search'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/friends/search'
	);

	///

	function v2_profiles_friends_add($uid1,$uid2) {

		$u1 = user_load($uid1);
		$u2 = user_load($uid2);

		if (!in_array('can_make_friends', $u1->roles)) {
			drupal_set_message('Your parent has not given you permission to make friends.');
		}

		if (!in_array('can_make_friends', $u2->roles)) {
			drupal_set_message("This user's parent has not given him or her permission to make friends.");
		}

		if (in_array('can_make_friends', $u1->roles) && in_array('can_make_friends', $u2->roles)) {
			user_relationships_request_relationship($u1, $u2, 4, false);
			drupal_set_message('This user has been notified that you would like to be friends.');
			drupal_goto('user/'.$u1->uid.'/friends/browse');
		}

		drupal_goto('user');

	}

	function v2_profiles_friends_approve($uid1,$uid2) {

		$u1 = user_load($uid1);
		$u2 = user_load($uid2);

		$relationship = user_relationships_load(array('between' => array($u1->uid,$u2->uid)));
		$relationship = array_pop($relationship);

		if ($relationship) {
  		v2_profiles_feed_insert($u1->uid,88,95,'Feed ' . time(),'','<a href="/user/' . $u1->uid . '">' . $u1->name . '</a> has added <a href="/user/' . $u2->uid . '">' . $u2->name . '</a> as a friend.');
  		v2_profiles_feed_insert($u2->uid,88,95,'Feed ' . time(),'','<a href="/user/' . $u2->uid . '">' . $u2->name . '</a> has added <a href="/user/' . $u1->uid . '">' . $u1->name . '</a> as a friend.');

			user_relationships_save_relationship($relationship,'approve');
		}

		drupal_set_message('You have confirmed this user as your friend.');
		drupal_goto('user/'.$u1->uid.'/friends/browse');

	}

	function v2_profiles_friends_browse($uid,$limit=0) {

		$data = new stdClass();

		$user = user_load($uid);

		$requests = v2_profiles_friends_query_requests($user->uid);

		$friends = v2_profiles_friends_query($user->uid);

		if ($limit > 0) {
			//$friends = array_slice($friends, 0, $limit);
		}

		$data->items->requests = $requests;
		$data->items->friends = $friends;
		$data->limit = $limit;
		$data->user = $user;

		return theme('v2_profiles_friends_browse', $data);

	}

	function v2_profiles_friends_ignore($uid1, $uid2) {

		$u1 = user_load($uid1);
		$u2 = user_load($uid2);

		$relationship = user_relationships_load(array('between' => array($u1->uid,$u2->uid)));
		$relationship = array_pop($relationship);

		if ($relationship) {
			user_relationships_delete_relationship($relationship, $u1);
		}

		drupal_set_message('You have cancelled this friendship request.');
		drupal_goto('user/'.$u1->uid.'/friends/browse');

	}

	function v2_profiles_friends_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$all = v2_profiles_friends_query_all($user->uid); shuffle($all);
		$friends = v2_profiles_friends_query($user->uid);

		// TODO: filter things out

		$data->items->all = array_slice($all, 0, 10);
		$data->items->friends = $friends;

		return theme('v2_profiles_friends_index', $data);

	}

	function v2_profiles_friends_query($uid) {

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
				`ur`.`rtid` = 4 AND
				`ur`.`approved` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
      $diff_schools = cmwn_school_students_different_school($user,user_load($result->uid));
      
      if(!$diff_schools){
  			$item = array(
  				'href' => '/user/'.$user->uid.'/friends/'.$result->uid,
  				'name' => $result->name,
  				'src' => v2_profiles_avatars_query($result->uid),
  				'uid' => $result->uid,
  			);
  			$items[] = (object)$item;        
      }
		}
		return $items;
		
	}

	function v2_profiles_friends_query_all($uid, $q = '', $tid = 0) {

		$items = array();

		$user = user_load($uid);

		$filter_friends = '';
		$profile_type = 'child_profile';
		switch($user->user_type){
			case 'parent':
				$filter_friends = ' and u.uid in (select uid from users_roles uri where uri.rid = 5 and uri.uid = u.uid) ';
				$profile_type = 'parent_profile';
				break;

			case 'teacher':
				$filter_friends = ' and u.uid in (select uid from users_roles uri where uri.rid = 6 and uri.uid = u.uid) ';
				$profile_type = 'teacher_profile';
				break;

			default:
				break;
		}

		$query = "
			SELECT
				`u`.`uid`,
				`u`.`name`,
				`ur2`.`approved`
			FROM
				`users` AS `u` JOIN
				`node` AS `n` ON `u`.`uid` = `n`.`uid` AND `n`.`type` = '" . $profile_type ."' JOIN
				`users_roles` AS `ur` ON `u`.`uid` = `ur`.`uid` JOIN
				`role` AS `r` ON `ur`.`rid` = `r`.`rid` LEFT JOIN
				`user_relationships` AS `ur2` ON `u`.`uid` = `ur2`.`requestee_id` AND `ur2`.`requester_id` = " . $user->uid . " LEFT JOIN
				`term_node` AS `tn` ON `n`.`nid` = `tn`.`nid`
			WHERE
				`r`.`rid` = 28 " . $filter_friends . "
				" . ((!empty($q))?"AND `u`.`name` LIKE '%%" . db_escape_string($q). "%%'":"") . "
				" . (($tid>0)?"AND `tn`.`tid` = " . $tid:"") . "
			ORDER BY
				`u`.`name`;
		";
//print $query;
		$results = db_query($query);

		while ($result = db_fetch_object($results)) {

			if ($result->uid == $user->uid) continue;
			if ($result->approved == 1) continue;
			$relationship = user_relationships_load(array('between' => array($result->uid , $user->uid)));
			$relationship = array_pop($relationship);

      $diff_schools = cmwn_school_students_different_school($user,user_load($result->uid));

      if(!$diff_schools){				
  			$item = array(
  				'href' => '/user/'.$user->uid.'/friends/'.$result->uid,
  				'name' => $result->name,
  				'src' => v2_profiles_avatars_query($result->uid),
  				'relationship' => $relationship,
  				'requested' => ($result->approved == '')?0:1,
  				'uid' => $result->uid,
  			);
  			$items[] = (object)$item;
  		}
		}

		return $items;

	}

	function v2_profiles_friends_query_requests($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$query = "
			SELECT
				`u`.`uid`,
				`u`.`name`
			FROM
				`user_relationships` AS `ur` JOIN `users` AS `u` ON `ur`.`requester_id` = `u`.`uid`
			WHERE
				`ur`.`requestee_id` = " . $user->uid . " AND
				`ur`.`rtid` = 4 AND
				`ur`.`approved` = 0;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$item = array(
				'href' => '/user/'.$user->uid.'/friends/'.$result->uid,
				'name' => $result->name,
				'src' => v2_profiles_avatars_query($result->uid),
				'uid' => $result->uid,
			);
			$items[] = (object)$item;
		}

		return $items;

	}

	function v2_profiles_friends_read($uid1, $uid2) {

		$data = new stdClass();

		$user = user_load($uid2);

		$relationship = user_relationships_load(array('between' => array($uid1, $uid2)));
		$relationship = array_pop($relationship);

		$data->relationship = $relationship;
		$data->user = $user;

		return theme('v2_profiles_friends_read', $data);

	}

	function v2_profiles_friends_remove($uid1,$uid2) {

		$u1 = user_load($uid1);
		$u2 = user_load($uid2);

		$relationship = user_relationships_load(array('between' => array($u1->uid,$u2->uid)));
		$relationship = array_pop($relationship);

		if ($relationship) {
			user_relationships_delete_relationship($relationship,$u1);
		}

		drupal_set_message('You have removed this user as your friend.');
		drupal_goto('user/'.$u1->uid.'/friends/browse');

	}

	function v2_profiles_friends_search($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$q = '';
		if (sizeof($_POST) > 0) {
			$q = ($_POST['q'])? $_POST['q'] : '';
		}

		$tid = 0;
		if (arg(4)) {
			$tid = intval(arg(4));
		}
		$tids = array();
		$child = ChildUser::castAs($user);
		if ($child) {
			foreach ($child->getChildProfile()->taxonomy as $term) {
				$tids[] = $term->tid;
			}
		}
		$interests = array();
		$terms = taxonomy_get_tree(3);
		foreach ($terms as $term) {
			$interest = new stdClass();
			$interest->class = 'id-'.str_pad($term->tid,3,'0',STR_PAD_LEFT).((in_array($term->tid,$tids))?' active':'');
			$interest->href = '/user/'.$uid.'/friends/search/'.$term->tid;
			$interest->title = $term->name;
			$interests[] = $interest;
		}

		$items = v2_profiles_friends_query_all($user->uid, $q, $tid);

		$data->interests = $interests;
		$data->items = $items;
		$data->user = $user;

		return theme('v2_profiles_friends_search', $data);

	}
