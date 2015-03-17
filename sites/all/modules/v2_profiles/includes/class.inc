<?php
	$v2_profiles_menu_items["user/%/class"] = array(	
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_class_index",
		"title" => "My Class",
		"type" => MENU_CALLBACK,
	);


	$v2_profiles_theme_items['v2_profiles_class_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/class/index'
	);
	
	function v2_profiles_class_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);
		
		$uids = array(5018, 4953, 4964,5020, 5019, 5017, 4996, 4985, 4983, 4981, 4979, 4977, 4974, 4971, 4980);
		
		$uids_placeholder = db_placeholders($uids);
		
		$s_uids = db_query("select uid from {users} where uid in ($uids_placeholder)", $uids);

    $students = array();

    while($student = db_fetch_object($s_uids)){  
      $student = user_load($student->uid);
      //get avatar
      $avatar = v2_profiles_avatars_query($student->uid);
      $student->avatar = $avatar;
      //count flips

			$total_earned_flips = 0;
			$flipstuff = v2_profiles_flips_query_all($student->uid);
			foreach($flipstuff as $key=>$val) {
				if($val->progress=='100') $total_earned_flips++;
			}
      $student->total_earned_flips = $total_earned_flips;
      
      //get flips
      $student->flips = $flipstuff;
      $students[] = $student;
    }
    $data->students = $students;
    
		$data->user = $user;
    $resources = theme('v2_profiles_resource_center_index', theme('image', 'sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg'));
		return $resources . theme('v2_profiles_class_index', $data);
	}