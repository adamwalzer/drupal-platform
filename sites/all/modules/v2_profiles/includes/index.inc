<?php

	/* 1.4 */

	$v2_profiles_theme_items['v2_profiles_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/index',
	);

	function v2_profiles_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$data->user = $user;

		return theme('v2_profiles_index', $data);

	}