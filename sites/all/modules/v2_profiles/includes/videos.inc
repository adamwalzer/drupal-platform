<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/videos"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_videos_index",
		"title" => "Videos",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/videos/%"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_videos_read",
		"title" => "Videos",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_videos_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/videos/index'
	);

	$v2_profiles_theme_items['v2_profiles_videos_partner'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/videos/partner'
	);

	$v2_profiles_theme_items['v2_profiles_videos_read'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/videos/read'
	);

	function v2_profiles_videos_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$items = new stdClass();

		$items->group2 = v2_profiles_videos_query_user($uid);

		$items->group3 = v2_profiles_videos_query_cmwn();

		$friend_uids = array(0);
		$friends = v2_profiles_friends_query($uid);
		foreach ($friends as $friend) {
			$friend_uids[] = $friend->uid;
		}
		$items->group4 = v2_profiles_videos_query_friends($friend_uids);

		$school = v2_profiles_school_query($uid);
		$items->group5 = v2_profiles_videos_query_schools($school->nid);

		$items->group1 = array_merge($items->group2, $items->group3, $items->group4, $items->group5);

		$data->items = $items;
		$data->user = $user;

		return theme('v2_profiles_videos_index', $data);

	}

	function v2_profiles_videos_partner($nid) {

		global $user;

		$data = new stdClass();

		$items = new stdClass();

		$items->group1 = v2_profiles_videos_query_partner($nid);
		$items->group2 = v2_profiles_videos_query_partner($nid);

		$data->items = $items;
		$data->user = $user;

		return theme('v2_profiles_videos_partner', $data);

	}

	function v2_profiles_videos_query_cmwn() {

		$items = array();

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n` JOIN
				`content_field_school` AS `cfs` ON `n`.`nid` = `cfs`.`nid` AND `n`.`type` = 'video'
			WHERE
				`n`.`uid` = 1 AND
				`cfs`.`field_school_nid` IS NULL AND
				`n`.`status` = 1 order by RAND();
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}

	function v2_profiles_videos_query_friends($uids) {

		$items = array();

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n` JOIN
				`content_field_school` AS `cfs` ON `n`.`nid` = `cfs`.`nid` AND `n`.`type` = 'video'
			WHERE
				`n`.`uid` IN (".implode($uids,',').") AND
				`cfs`.`field_school_nid` IS NULL AND
				`n`.`status` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}

	function v2_profiles_videos_query_partner($nid) {

		$items = array();

		return $items;

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n`
			WHERE
				`n`.`nid` = " . $nid . " AND
				`n`.`status` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}

	function v2_profiles_videos_query_schools($nid) {

		$items = array();

		$node = node_load($nid);

		if (!$node) return $items;

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n` JOIN
				`content_field_school` AS `cfs` ON `n`.`nid` = `cfs`.`nid` AND `n`.`type` = 'video'
			WHERE
				`cfs`.`field_school_nid` = " . $node->nid . " AND
				`n`.`status` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}

	function v2_profiles_videos_query_user($uid) {

		$items = array();

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n` JOIN
				`content_field_school` AS `cfs` ON `n`.`nid` = `cfs`.`nid` AND `n`.`type` = 'video'
			WHERE
				`n`.`uid` = ".$uid." AND
				`cfs`.`field_school_nid` IS NULL AND
				`n`.`status` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}

	function v2_profiles_videos_read($uid,$nid) {

		$data = new stdClass();

		$user = user_load($uid);

		$item = node_load($nid);

		$data->item = $item;
		$data->user = $user;

		print theme('v2_profiles_videos_read', $data);

		exit();

	}