<?php
	$v2_profiles_menu_items["user/%/class"] = array(
		"access arguments" => array(1,2),
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

  $v2_profiles_theme_items['v2_profiles_class_flips_progress'] = array(
    'arguments' => array('data' => array()),
    'template' => 'templates/class/class_flips_progress'
  );


	function v2_profiles_class_index($uid,$class_nid) {
    //PROBLEM: this assumes $uid is teacher...student needs class too.
    //Problem update - this code doesn't care if uid is a teacher, it doesn'te ven use it.

    
    //LOAD STUDENTS
		//$user = user_load($uid);

    $class_flips_progress = array();
    $class_flips = array();

		$uids = array();

      $data = new stdClass();
      $data->readonly = v2_profiles_whiteboard_readonly();
      $data->class = node_load($class_nid);
      $uids_view_array =  cmwn_views_get_view_result('students_by_class','default',$class_nid);

      foreach($uids_view_array as $row){
        $uids[] = $row->uid;
      }

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
          if($val->progress=='100'){
           $total_earned_flips++;
           $class_flips_progress['complete'][$val->id] = $val;
          }else{
            $class_flips_progress['incomplete'][$val->id] = $val;
          }
          if(!isset($class_flips[$val->id])){
            $class_flips[$val->id] = node_load($val->id);
          }
        }
        $student->total_earned_flips = $total_earned_flips;

        //get flips
        $student->flips = $flipstuff;
        $students[] = $student;
      }
      $data->students = $students;
      $data->class_flips_progress = $class_flips_progress;
      $data->class_flips = $class_flips;
      $data->user = $user;
      
      //LOAD CLASS WHITEBOARD POSTS
   		$items = v2_profiles_whiteboard_query_class($class_nid);
  
  		$data->items = $items;
  		$data->user = $user;
      if($data->user->user_type == 'child'){
        $flips_progress  = theme('v2_profiles_class_flips_progress', $data);        
      }

      return $flips_progress . theme('v2_profiles_class_index', $data);
    //}

    //return $all_classes;
 	}


function v2_profiles_class_flips_progress($uid) {

    $data = new stdClass();

    $user = user_load($uid);

    $class_flips_progress = array();
    $class_flips = array();

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
        if($val->progress=='100'){
         $total_earned_flips++;
         $class_flips_progress['complete'][$val->id] = $val;
        }else{
          $class_flips_progress['incomplete'][$val->id] = $val;
        }
        if(!isset($class_flips[$val->id])){
          $class_flips[$val->id] = node_load($val->id);
        }
      }
      $student->total_earned_flips = $total_earned_flips;

      //get flips
      $student->flips = $flipstuff;
      $students[] = $student;
    }
    $data->students = $students;
    $data->class_flips_progress = $class_flips_progress;
    $data->class_flips = $class_flips;
    $data->user = $user;
    //$resources = theme('v2_profiles_resource_center_index', theme('image', 'sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg'));
    //return $resources . theme('v2_profiles_class_index', $data);

    return theme('v2_profiles_class_index', $data);
  }

function v2_profiles_class_unflipped_flips($completed_flip_nids = array()) {

    $items = array();

    //TODO update with proper db_placeholders()
    $query = "select nid from {node} n where nid not in (" . implode(',',$completed_flip_nids) . ") and n.status > 0 and n.type='flip' limit 4";
    //print $query;exit;
    $results = db_query($query);

    while ($result = db_fetch_object($results)) {

      $items[] = node_load($result->nid);
    }

    return $items;

  }


	function v2_profiles_class_get_profile_classes($user){
  	switch($user->user_type){
    	case 'teacher':
      	return content_profile_load('teacher_profile', $user->uid)->field_teacher_classes;
    	  break;
    	 
      case 'child':
      	return content_profile_load('child_profile', $user->uid)->field_student_classes;
        break;
      
      default:
        return false;
        break;
  	}
	}
	
	function v2_profiles_has_class($user, $class_nid){
  	
  	$classes = v2_profiles_class_get_profile_classes($user);
  	$class_flat = array();
  	
  	foreach($classes as $class){
      $class_flat[] = $class['nid'];
    }
    
    if(!in_array($class_nid,($class_flat))){
      return false;
    }else{
      return true;
    }
    
	}