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

	$v2_profiles_menu_items["school/%/dashboard"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_school_dashboard_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_school_dashboard",

		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_school_dashboard'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/school/dashboard'
	);

	function v2_profiles_school_index($uid) {

		$data = new stdClass();
    $data->readonly = v2_profiles_whiteboard_readonly();
		$user = user_load($uid);

		$school = v2_profiles_school_query($uid);

		$data->school = $school;
		$data->user = $user;
		
		
		$data->items = v2_profiles_whiteboard_query($uid, 'School');
		

		return theme('v2_profiles_school_index', $data);

	}

	function v2_profiles_school_dashboard($school_id){
		$data = new stdClass();

		$school = node_load($school_id);

		$data->school = $school;

		return theme('v2_profiles_school_dashboard', $data);
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


function v2_profiles_school_import(){
	$form = array();
	// If this #attribute is not present, upload will fail on submit
	
	$form['#attributes']['enctype'] = 'multipart/form-data';
	$form['school_import'] = array(
		'#title' => t(''),
		'#type'  => 'file',

	);
	
	$form['submit_upload'] = array(
		'#type'  =>  'submit',
		'#value'  =>  'Upload Spreadsheet'
	);
	
	return $form;
}


function v2_profiles_school_import_submit($form, &$form_state) {

  $validators = array();
  $dest = 'sites/default/files/school_bulk_imports';
  $file = file_save_upload('school_import', $validators, $dest, FILE_EXISTS_RENAME);
  //$file will be 0 if the upload doesn't exist, or the $dest directory
  //isn't writable
  if ($file != 0) {
    //Success, $file object will contain a different (renamed)
    //filename and filepath if the destination existed
    drupal_set_message('File uploaded.');
    //dsm($file);

    //load excel into a multidimensional array
		module_load_include('inc', 'phpexcel', 'phpexcel.api');

		// The path to the excel file
		$path = $file->filepath;

		$result = phpexcel_import($path);

		if (is_array($result)) {
		  drupal_set_message(t("Spreadsheet uploaded...checking format."));

			$dryrun = v2_profiles_school_import_spreadsheet_validate($result);

			if(!$dryrun['pass']){//Start with a "dry" - validate spreadsheet.
			//if(false){//swap this and above if statement to enable dry run - should be enabled for testing and production.
				drupal_set_message(t('*** The spreadsheet you uploaded has errors. Import has been aborted and no new records were created or updated. Please review the above errors, correct the spreadsheet, and try again.'), 'error');
			}else{//dry run passed - go ahead and make and/or update the records.
				drupal_set_message(t('Spreadsheet format passed validation.'));
				//keep track of nodes and users created in case (gasp) we want to roll back
				//node creation. This won't save updated nodes.
				$new_nodes = array();
				$new_users = array();

				//keep track of updated nodes in case we need to roll back.
				//ideally rollback shouldn't happen because dry run should catch errors but stranger things have happened so we'll keep this option open.
				$updated_nodes = array();
				$updated_users = array();

				$grades = v2_profiles_grade_array();

				//District should already exist as it is created manually. Dry run will catch this.

				//Import/Update School
				//$result[0] = Classes
				//$result[1] = Teachers
				//$result[2] = Students
				global $user;
				//get the $school node of the currently logged in School Administrator.
				$school_nid = db_result(db_query('select nid from {node} n where type="school" and uid = %d order by nid desc', $user->uid));
				$school = node_load($school_nid);
				//dsm($school);
				//$school has the node object of existing school in db.
				//Import classes - if existing, skip. Otherwise insert.
				$classes = $result[0];
				$classes_nodes = array();
				foreach($classes as $class){
					$classes_nodes[$class['Class Number']] = v2_profiles_school_import_class($school, $class);//$classes_nodes contains drupal nodes of the actual class which contains class nid which we'll use for later node references on teacher and student nodes. Can be easily referenced by Class Number indices
				}
				//Import Teachers - if existing, skip. Otherwise insert, base profile, teacher profile, account starts as inactive
				$teachers = $result[1];
				$teachers_users = array();
				foreach($teachers as $teacher){
					$teachers_users[$teacher['Email Address']] = v2_profiles_school_import_teacher($school, $teacher, $classes_nodes);
				}


				//Import Students - if existing, skip. Otherwise insert, base profile, child profile.
				// - Also, create parents user account (only update if same email address), base profile
				//   and parent profile. starts as inactive
				$students = $result[2];
				$students_users = array();
				foreach($students as $student){
					$students_users[$student['Email Address']] = v2_profiles_school_import_student($school, $student, $classes_nodes, $grades);
				}
			}

			//erase the spreadsheet from the server!
			file_delete($file->filepath);
			drupal_set_message(t('Spreadsheet Import Complete!'));
		}
		else {
		  drupal_set_message(t("Oops ! An error occured !"), 'error');
		}

  }
  else {
    form_set_error('v2_profiles_school_import_submit', t("Failed to save the file."));
  }
}

function v2_profiles_school_import_spreadsheet_validate($result){
	//iterate through entire spreadsheet and find any problems that indicate
	//spreadsheet should not be imported, alert user and abort import
	//if any issues are found.
	global $user;
	$dryrun = array();
	$dryrun['pass'] = true;

	//First, check if this district exists. If it does not, something is terribly wrong
	//because w/o the district, there should be no school administrator
	/*
	$district = $result[0][0];
	$district_existing = node_load(array('title' => $district['District Name']));
	if(!$district_existing){
		$dryrun['pass'] = false;
		drupal_set_message(t('District by this name not found!'), 'error');
	}elseif($district->field_district_number[0]['value'] != $district['District Number']){
		$dryrun['pass'] = false;
		drupal_set_message(t('District by this name was found, but it does not match the existing district number.'), 'error');
	}*/

	//check if the school exists
	$school_nid = db_query('select nid from {node} n where type="school" and uid = %d', $user->uid);
	if(!$school_nid){
		$dry_run['pass'] = false;
		drupal_set_message(t('School associated with this account not found.'), 'error');
	}

	//check duplicate/problems teacher email address
	//check class number assigned to more than one teacher.
	$all_emails = array();
	$teacher_emails = array();
	$teacher_class_numbers = array();
	foreach($result[1] as $teacher){
		$all_emails[] = $teacher['Email Address'];
		$teacher_emails[] = $teacher['Email Address'];

		if(!valid_email_address($teacher['Email Address']) && $teacher['First Name'] != ''){
			$dryrun['pass'] = false;
			drupal_set_message(t('Invalid teacher email address found! (@email)', array('@email' => $teacher['Email Address'])), 'error');
		}

		//loop through class numbers
		$classes = explode(',', $teacher['Class Number']);
		foreach($classes as $class){
			if($class != ''){
				$teacher_class_numbers[] = $class;
			}
		}

	}
	//check dup teacher emails
	if(count(array_filter($teacher_emails)) !== count(array_unique(array_filter($teacher_emails)))){
		$dryrun['pass'] = false;
		drupal_set_message(t('Duplicate teacher email addresses found!'), 'error');
	}

	//check dup class number assignment
	if(count($teacher_class_numbers) !== count(array_unique($teacher_class_numbers))){
		$dryrun['pass'] = false;
		$diff = implode(', ',array_filter(array_diff_assoc($teacher_class_numbers, array_unique($teacher_class_numbers))));
		drupal_set_message(t('Duplicate teacher Class Number assignment found - @class_numbers', array('@class_numbers' => implode(', ', $diff))), 'error');
	}

	//check children's data - if one is certainly in wrong format, reject spreadsheet as others are in question
	$children = $result[2];
	$child_emails = array();
	$parent_emails = array();
	foreach($children as $child){
		if(trim($child['Email Address']) != ''){
			$all_emails[] = $child['Email Address'];
			$child_emails[] = $child['Email Address'];
		}

		if(trim($child['Guardian Email Address']) != ''){
			$parent_emails[] = $child['Guardian Email Address'];
		}

		$month = explode('/',$child['DOB MM/DD/YYYY']);//THIS INDEX MAY CHANGE TO MM/DD/YYYY
		if((int)$month[0] > 12){
			$dryrun['pass'] = false;
			drupal_set_message(t('Birthdate format error detected for @student. Date must be MM/DD/YYYY.', array('@student'=>$child['First Name'] . ' ' . $child['Last Name'])), 'error');
		}
	}

	//check for duplicate
	if(count(array_filter($all_emails)) !== count(array_unique(array_filter($all_emails)))){
		$dryrun['pass'] = false;
		$diff = implode(', ',array_filter(array_diff_assoc(array_filter($all_emails), array_unique(array_filter($all_emails)))));
		drupal_set_message(t('Duplicate email addresses found across Teacher and Student Records - @emails', array('@emails' => $diff)), 'error');
	}

	//check for any child email matching any parent email
	$child_parent_email_overlap = array_filter(array_intersect($parent_emails, $child_emails));
	if(count($child_parent_email_overlap) > 0){
		$dryrun['pass'] = false;

		drupal_set_message(t('Duplicate email addresses found between parent and child records. Child cannot have the same email address as a parent - @emails', array('@emails' => implode(', ', $child_parent_email_overlap))), 'error');
	}

	//TODO checks:
	//Check for teacher email address already in system as non teacher role

	//Check for child email address in system as non child role.

	//check for parent/guardian email address in system as non parent role.

	return $dryrun;
}

/**
 * Import
 *
 * @param string $op
 *        The current operation
 * @param * &$data
 *        The data. Depends on the operation. See documentation below for more
 *        information
 * @param PHPExcel_Reader|PHPExcel_Worksheet|PHPExcel_Cell $phpexcel
 *        The current object used. Can either be a PHPExcel_Reader object when
 *        loading the Excel file, a PHPExcel_Worksheet object when iterating
 *        through the worksheets or a PHPExcel_Cell object when reading data
 *        from a cell
 * @param array $options
 *        The options for the phpexcel import
 * @param int $column
 *        (optional) the column number
 * @param int $row
 *        (optional) the row number
 */
function v2_profiles_phpexcel_import($op, &$data, $phpexcel, $options, $column = NULL, $row = NULL) {
  switch ($op) {
    case 'full':
      /**
       * The $data parameter will contain the fully loaded Excel file, returned
       * by the PHPExcel_Reader object.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'sheet':
      /**
       * The $data parameter will contain the current PHPExcel_Worksheet.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'row':
      /**
       * The $data parameter will contain the current PHPExcel_Row.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'pre cell':
      /**
       * The $data parameter will contain the current cell value. The value has
       * not been added to the data array and can still be altered.
       *
       * The $phpexcel parameter will contain the PHPExcel_Cell object.
       *
       * The $column and $row parameters are set.
       */
      break;

    case 'post cell':
      /**
       * The $data parameter will contain the current cell value inside the data
       * array. The value can be altered.
       *
       * The $phpexcel parameter will contain the PHPExcel_Cell object.
       *
       * The $column and $row parameters are set.
       */
      break;
  }
}


function v2_profiles_school_import_class($school, $class){
	global $user;
	$classes_existing = db_query('select nid from {node} n where n.title = "%s" and type="class" and uid = %d',$class['Class Name'], $user->uid);
	while($class_existing = db_fetch_object($classes_existing)){
		$class_existing = node_load($class_existing->nid);
		if($class_existing->field_class_school[0]['nid'] == $school->nid &&
			//$class_existing->field_class_building_number[0]['value'] == $class['Building Number'] &&
			//$class_existing->field_class_room_number[0]['value'] == $class['Room Number'] &&
				$class_existing->field_class_number[0]['value'] == $class['Class Number']){//it's the right class. We don't check room/buildings cuz this could change.
				return $class_existing;//send back the existing class node.
		}
	}
	//if we got here, that means there is no existing class node and we need to create it.
	$new_class = (object) NULL;
	$new_class->type = 'class';
	$new_class->title = $class['Class Name'];
	$new_class->uid = $user->uid;
	$new_class->created = strtotime("now");
	$new_class->changed = strtotime("now");
	$new_class->status = 1;
	$new_class->comment = 0;
	$new_class->promote = 0;
	$new_class->moderate = 0;
	$new_class->sticky = 0;

	// add CCK field data
	$new_class->field_class_number[0]['value'] = $class['Class Number'];
	//$new_class->field_field_class_grade[0]['nid'] = $class['Class Number']; //node reference, this is in question as to whether we want to store this with the class - past discussion indicated not to.
	$new_class->field_class_school[0]['nid'] = $school->nid;
	$new_class->field_class_building_number[0]['value'] = $class['Building Number'];
	$new_class->field_class_room_number[0]['value'] = $class['Room Number'];
//drupal_set_message('class object before node_save: ' . print_r($new_class, true));
	// save new class, return it.

	//node_submit($new_class);
	node_save($new_class);

	//drupal_set_message('class object after node_save: ' . print_r($new_class, true));
	v2_profiles_school_push_class($school, $new_class);
	node_save($school);

	return $new_class;
}

//TODO: link classes to teacher profiles
function v2_profiles_school_import_teacher($school, $teacher, $classes_nodes){
	//absolute unique identifier is always email address. There can only be one drupal
	//user account per email address.
	$teacher_existing = user_load(array('mail'=> $teacher['Email Address']));
	if($teacher_existing){//hope this teacher has a profile.
		return $teacher_existing;
	}else{//create new teacher account.
		//find unique username
		$username = $teacher['First Name'] . $teacher['Last Name'];
		$ctr = 1;
		while(db_result(db_query('select name from {users} u where name = "%s" limit 1', $username))){
			$username = $teacher['First Name'] . $teacher['Last Name'] . '_' . $ctr;
			$ctr++;
		}

		//generate password
		$bytes = openssl_random_pseudo_bytes(2);
		$pwd = bin2hex($bytes);

		//TODO: ADD ROLES
		$new_teacher = array(
			'name' => $username,
			//'pass' => $pwd,
			'pass' => 'test',
			'mail' => $teacher['Email Address'],
			'access' => '0',
			'status' => 1,
			'user_type' => 'teacher',
			'roles' => array(
				6 => 'teacher',
				28 => 'can_make_friends',
			),
		);

		$new_teacher = user_save(NULL, $new_teacher, NULL);
		//print_r($new_teacher->uid);exit;
		//drupal_set_message('school id: ' . $school->nid);
		v2_profiles_school_push_teacher($school, $new_teacher);
		node_save($school);

		//Base Profile
		$base_profile = (object) NULL;
		$base_profile->type = 'base_profile';
		$base_profile->title = $username;
		$base_profile->uid = $new_teacher->uid;
		$base_profile->created = strtotime("now");
		$base_profile->changed = strtotime("now");
		$base_profile->status = 1;
		$base_profile->comment = 0;
		$base_profile->promote = 0;
		$base_profile->moderate = 0;
		$base_profile->sticky = 0;

		// add CCK field data
		$base_profile->field_first_name[0]['value'] = $teacher['First Name'];
		$base_profile->field_last_name[0]['value'] = $teacher['Last Name'];
		$base_profile->field_gender[0]['value'] = $teacher['Gender'];

		// save new profile
		//$base_profile = node_submit($base_profile);
		//$base_profile =
		node_save($base_profile);

		//Teacher Profile
		$teacher_profile = (object) NULL;
		$teacher_profile->type = 'teacher_profile';
		$teacher_profile->title = $username;
		$teacher_profile->uid = $new_teacher->uid;
		$teacher_profile->created = strtotime("now");
		$teacher_profile->changed = strtotime("now");
		$teacher_profile->status = 1;
		$teacher_profile->comment = 0;
		$teacher_profile->promote = 0;
		$teacher_profile->moderate = 0;
		$teacher_profile->sticky = 0;

		// add CCK field data
		$teacher_profile->field_school[0]['nid'] = $school->nid;

		//add all classes!
		$classes = array_map('trim', explode(',', $teacher['Class Number']));
		for($i = 0; $i < count($classes); $i++){
			$teacher_profile->field_teacher_classes[$i]['nid'] = $classes_nodes[$classes[$i]]->nid;
		}
		// save new teacher profile
		$teacher_profile = node_submit($teacher_profile);
		$teacher_profile = node_save($teacher_profile);

		return $new_teacher;
	}
}

function v2_profiles_grade_array(){
	$grades = array();
	$grades_result = db_query('select nid, title from {node} n where type="grade" order by created desc');

	while($grade = db_fetch_object($grades_result)){
		$grades[$grade->title] = $grade->nid;
	}

	return $grades;
}

//TODO: link student profiles to classes.
function v2_profiles_school_import_student($school, $student, $classes_nodes, $grades){//NOTE, $student also contains guardian info which needs to be dealt with also.
	$student_existing = user_load(array('mail'=> $student['Email Address']));
	if($student_existing){//hope this teacher has a profile.
		return $student_existing;
	}else{//create new teacher account.
		//find unique username
		$username = $student['First Name'] . $student['Last Name'];
		$ctr = 1;
		while(db_result(db_query('select name from {users} u where name = "%s" limit 1', $username))){
			$username = $student['First Name'] . $student['Last Name'] . '_' . $ctr;
			$ctr++;
		}

		//generate password
		$bytes = openssl_random_pseudo_bytes(2);
		$pwd = bin2hex($bytes);

		//TODO: ADD ROLES
		$new_student = array(
			'name' => $username,
			//'pass' => $pwd,
			'pass' => 'test',
			'mail' => $student['Email Address'],
			'parent_email' => $student['Guardian Email Address'],
			'access' => '0',
			'status' => 1,
			'user_type' => 'child',
			'roles' => array(
		    4 => 'child',
		    7 => 'child_can_upload_pictures',
		    8 => 'child_can_upload_videos',
		    9 => 'child_can_make_friends',
		    10 => 'approved-child',
		    27 => 'can_upload_media',
		    28 => 'can_make_friends',
		    29 => 'can_receive_notices',
		    30 => 'can_upload_flip_media',
		    31 => 'can_receive_notices_via_parent',
			),
		);

		$new_student = user_save(NULL, $new_student, NULL);

		//Base Profile
		$base_profile = (object) NULL;
		$base_profile->type = 'base_profile';
		$base_profile->title = $username;
		$base_profile->uid = $new_student->uid;
		$base_profile->created = strtotime("now");
		$base_profile->changed = strtotime("now");
		$base_profile->status = 1;
		$base_profile->comment = 0;
		$base_profile->promote = 0;
		$base_profile->moderate = 0;
		$base_profile->sticky = 0;

		// add CCK field data
		$base_profile->field_first_name[0]['value'] = $student['First Name'];
		$base_profile->field_last_name[0]['value'] = $student['Last Name'];
		$base_profile->field_gender[0]['value'] = $student['Gender'];

		// save new profile
		//$base_profile = node_submit($base_profile);
		//$base_profile =
		node_save($base_profile);


		//Child Profile
		$child_profile = (object) NULL;
		$child_profile->type = 'child_profile';
		$child_profile->title = $username;
		$child_profile->uid = $new_student->uid;
		$child_profile->created = strtotime("now");
		$child_profile->changed = strtotime("now");
		$child_profile->status = 1;
		$child_profile->comment = 0;
		$child_profile->promote = 0;
		$child_profile->moderate = 0;
		$child_profile->sticky = 0;

		// add CCK field data
		$child_profile->field_school[0]['nid'] = $school->nid;

		//grade node ref
		if($student['Grade'] == 'PK') $student['Grade'] = "Pre-Kindergarten";
		if($student['Grade'] == 'K') $student['Grade'] = "Kindergarten";
		$child_profile->field_student_grade[0]['nid'] = $grades[$student['Grade']];

		//birthday
		$dob = explode('/',$student['DOB MM/DD/YYYY']);
		$child_profile->field_dob[0] = array(
			'value'=>$dob[2] . '-' . $dob[0] . '-' . $dob[1] . 'T00:00:00',
			'timezone' => 'America/New_York',
			'timezone_db' => 'America/New_York',
			'date_type' => 'date',
		);

		//add all classes!
		$classes = array_map('trim', explode(',', $student['Class Number']));
		for($i = 0; $i < count($classes); $i++){
			$child_profile->field_student_classes[]['nid'] = $classes_nodes[$classes[$i]]->nid;
			//drupal_set_message($classes_nodes[$classes[$i]]->nid);
			//drupal_set_message($classes[$i]);
		}

		// save new child profile
		//$child_profile = node_submit($child_profile);
		//drupal_set_message('child profile before node save: ' . print_r($child_profile,true));
		node_save($child_profile);
		//drupal_set_message('child profile after node save: ' . print_r($child_profile,true));

		//Import Parent
		$parent = v2_profiles_school_import_parent($school, $student);

		//Add Parent!
		v2_profiles_children_link_imported($parent->uid, $new_student->uid);

		return $new_student;
	}
}

function v2_profiles_school_import_parent($school, $student){//NOTE, $student also contains guardian info which needs to be dealt with also.
	$parent_existing = user_load(array('mail'=> $student['Guardian Email Address']));
	if($parent_existing){
		return $parent_existing;
	}else{//create new teacher account.
		//find unique username
		$username = $student['Guardian First Name'] . $student['Guardian Last Name'];
		$ctr = 1;
		while(db_result(db_query('select name from {users} u where name = "%s" limit 1', $username))){
			$username = $student['Guardian First Name'] . $student['Guardian Last Name'] . '_' . $ctr;
			$ctr++;
		}

		//generate password
		$bytes = openssl_random_pseudo_bytes(2);
		$pwd = bin2hex($bytes);

		//TODO: ADD ROLES
		$new_parent = array(
			'name' => $username,
			//'pass' => $pwd,
			'pass' => 'test',
			'mail' => $student['Guardian Email Address'],
			'access' => '0',
			'status' => 1,
			'user_type' => 'parent',
			'roles' => array(
				5 => 'parent',
				28 => 'can_make_friends',
				12 => 'verified-parent',
			),
		);
		//dsm($new_parent);
		$new_parent = user_save(NULL, $new_parent, NULL);

		//Base Profile
		$base_profile = (object) NULL;
		$base_profile->type = 'base_profile';
		$base_profile->title = $username;
		$base_profile->uid = $new_parent->uid;
		$base_profile->created = strtotime("now");
		$base_profile->changed = strtotime("now");
		$base_profile->status = 1;
		$base_profile->comment = 0;
		$base_profile->promote = 0;
		$base_profile->moderate = 0;
		$base_profile->sticky = 0;

		// add CCK field data
		$base_profile->field_first_name[0]['value'] = $student['Guardian First Name'];
		$base_profile->field_last_name[0]['value'] = $student['Guardian Last Name'];
		$base_profile->field_gender[0]['value'] = $student['Guardian Gender'];

		// save new profile
		//$base_profile = node_submit($base_profile);
		//$base_profile =
		node_save($base_profile);


		//Parent Profile
		$parent_profile = (object) NULL;
		$parent_profile->type = 'parent_profile';
		$parent_profile->title = $username;
		$parent_profile->uid = $new_parent->uid;
		$parent_profile->created = strtotime("now");
		$parent_profile->changed = strtotime("now");
		$parent_profile->status = 1;
		$parent_profile->comment = 0;
		$parent_profile->promote = 0;
		$parent_profile->moderate = 0;
		$parent_profile->sticky = 0;

		$parent_profile = node_submit($parent_profile);
		$parent_profile = node_save($parent_profile);

		return $new_parent;
	}
}

function v2_profiles_school_push_teacher(&$school, $teacher){
	$teachers_count = count($school->field_school_teachers);
	$school->field_school_teachers[]['uid'] = $teacher->uid;
	//return node_save($school);
}

function v2_profiles_school_push_class(&$school, $class){
	$classes_count = count($school->field_school_classes);
	//drupal_set_message('class_nid to add to school: ' . $class->nid);
	$school->field_school_classes[]['nid'] = $class->nid;
	//return node_save($school);
}
/*
//verify all parents above 5050
$uids = db_query('select uid from users where uid > 5050');
while($uid = db_fetch_object($uids)){
	$u = user_load($uid->uid);

	if(in_array('teacher', array_values($u->roles))){
		//dsm($u);

		//$u->roles[12] = 'verified-parent';
		//$update
		$update['roles'][2] = 'authenticated user';
		$update['roles'][6] = 'teacher';
		//$update['roles'][5] = 'parent';
		//$update['roles'][12] = 'verified-parent';
		$update['roles'][28] = 'can_make_friends';
		//user_save($u,$update);
	}
}
*/