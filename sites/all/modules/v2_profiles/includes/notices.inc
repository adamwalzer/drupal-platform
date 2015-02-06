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

	$v2_profiles_menu_items["user/%/notices/posting"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_notices_index_posting",
		"title" => "Notices - Posting",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/notices/account"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_notices_index_account",
		"title" => "Notices - Account",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/notices/award"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_notices_index_award",
		"title" => "Notices - Awward",
		"type" => MENU_CALLBACK,
	);
	
	$v2_profiles_theme_items['v2_profiles_notices_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index'
	);

	$v2_profiles_theme_items['v2_profiles_notices_index_posting'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index_posting'
	);

	$v2_profiles_theme_items['v2_profiles_notices_index_account'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index_account'
	);

	$v2_profiles_theme_items['v2_profiles_notices_index_award'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index_award'
	);

	function v2_profiles_notices_index($uid){

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_notices_index', $data);

	}
	
	
	function v2_profiles_notices_index_posting($uid){

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_notices_index_posting', $data);

	}
	
	function v2_profiles_notices_index_account($uid){

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_notices_index_account', $data);

	}	
	
  function v2_profiles_notices_index_award($uid){

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_notices_index_award', $data);

	}		