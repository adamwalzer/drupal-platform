<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/school"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_school_index",
		"title" => "school",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_school_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/school/index'
	);

	function v2_profiles_school_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$school = v2_profiles_school_query($uid);

		$data->school = $school;
		$data->user = $user;

		return theme('v2_profiles_school_index', $data);

	}

	function v2_profiles_school_query($uid) {

		$item = null;

		$user = user_load($uid);

		if (!$user) return $value;

		$query = "
			SELECT
				`cfs`.`field_school_nid` AS `nid`
			FROM
				`node` AS `n` JOIN
				`content_field_school` AS `cfs` ON `n`.`nid` = `cfs`.`nid` AND (`n`.`type` = 'child_profile' or n.type = 'teacher_profile')
			WHERE
				`n`.`uid` = " . $user->uid . " AND
				`n`.`status` = 1;
		";

		$value = intval(db_result(db_query($query)));

		if (empty($value)) return $item;

		return node_load($value);

	}
