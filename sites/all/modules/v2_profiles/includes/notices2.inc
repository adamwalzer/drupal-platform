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

	$v2_profiles_menu_items["user/%/notices/child/posting/%"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_notices_index_child_posting",
		"title" => "Notices - Child's Posting",
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
		"title" => "Notices - Award",
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
	
	$v2_profiles_theme_items['v2_profiles_notices_index_child_posting'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/notices/index_child_posting'
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

	function v2_profiles_notices_index_child_posting($uid){

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;
		
		$child_uid  = arg(5);
    $is_child = db_result(db_query('select requestee_id from {user_relationships} ur where requester_id = %d and rtid =2 and approved = 1', array($uid)));
    if($is_child){
  		$data->child = user_load($child_uid);
  		$data->child->avatar = v2_profiles_avatars_query($child_uid);
    }


		return theme('v2_profiles_notices_index_child_posting', $data);

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