<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/%/name'] = array(
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_name_index',
		'title' => 'Name',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_name_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/name/index'
	);

	function v2_profiles_name_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_name_index', $data);

	}