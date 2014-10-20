<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/notices"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_notices_index",
		"title" => "Notices",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_notices_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index'
	);

	function v2_profiles_notices_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_notices_index', $data);

	}