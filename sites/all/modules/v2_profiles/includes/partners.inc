<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/partners"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_partners_index",
		"title" => "Partners",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/partners/%"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_partners_read",
		"title" => "Partners",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_partners_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/partners/index'
	);

	$v2_profiles_theme_items['v2_profiles_partners_read'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/partners/read'
	);

	function v2_profiles_partners_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$items = v2_profiles_partners_query($uid);

		$data->items = $items;
		$data->user = $user;

		return theme('v2_profiles_partners_index', $data);

	}

	function v2_profiles_partners_read($uid,$nid) {

		$data = new stdClass();

		$user = user_load($uid);

		$item = node_load($nid);

		$data->item = $item;
		$data->user = $user;

		return theme('v2_profiles_partners_read', $data);

	}

	function v2_profiles_partners_query($uid) {

		$items = array();

		$user = user_load($uid);

		$query = "
			SELECT
				`n`.`nid` AS `nid`
			FROM
				`node` AS `n`
			WHERE
				`n`.`type` = 'brand_partner' AND
				`n`.`status` = 1;
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$items[] = node_load($result->nid);
		}

		return $items;

	}