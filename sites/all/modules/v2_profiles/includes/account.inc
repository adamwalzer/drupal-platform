<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/%/account'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_account_index',
		'title' => 'Account',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_account_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/account/index'
	);

	function v2_profiles_account_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$node = GenericUser::castAs($user)->getBaseProfile();

		if (sizeof($_POST) > 0) {

			$_step = $_POST['step']? intval($_POST['step']) : 0;

			switch ($_step) {

				case 1:

					$_password1 = $_POST['password1']? $_POST['password1'] : '';
					$_password2 = $_POST['password2']? $_POST['password2'] : '';

					if (!empty($_password1)) {
						if ($_password1 === $_password2) {
							db_query("UPDATE `users` SET `pass` = '" . db_escape_string(md5($_password1)) . "' WHERE `uid` = " . $user->uid . ";");
							drupal_set_message('Your profile was successfully updated.');
							drupal_goto('user/'.$user->uid.'/account');
						} else {
							drupal_set_message('Your passwords must match.', 'error');
						}
					} else {
						drupal_set_message('Please enter your password.', 'error');
					}

					break;

				case 2:

					$_email = $_POST['email']? $_POST['email'] : '';

					if (!empty($_email)) {
						$_count = db_result(db_query("SELECT COUNT(*) FROM `users` WHERE `mail` = '" . db_escape_string($_email) . "' AND `uid` <> " . $user->uid . ";"));
						if ($_count == 0) {
							if (!filter_var($_email, FILTER_VALIDATE_EMAIL)) {
								drupal_set_message('Please enter a valid email address.', 'error');
							} else {
								db_query("UPDATE `users` SET `mail` = '" . db_escape_string($_email) . "' WHERE `uid` = " . $user->uid . ";");
								drupal_set_message('Your profile was successfully updated.');
								drupal_goto('user/'.$user->uid.'/account');
							}
						} else {
							drupal_set_message('The email address is already taken, please choose another.', 'error');
						}
					} else {
						drupal_set_message('Please enter your email address.', 'error');
					}

					break;

				case 3:

					$_first_name = $_POST['first_name']? $_POST['first_name'] : '';
					$_last_name = $_POST['last_name']? $_POST['last_name'] : '';

					if (!empty($_first_name)) {
						if (!empty($_last_name)) {
							$node->field_first_name[0]['value'] = $_first_name;
							$node->field_last_name[0]['value'] = $_last_name;
							node_save($node);
							drupal_set_message('Your profile was successfully updated.');
							drupal_goto('user/'.$user->uid.'/account');
						} else {
							drupal_set_message('Please enter your last name.', 'error');
						}
					} else {
						drupal_set_message('Please enter your first name.', 'error');
					}

					break;

				case 4:

					$_username = $_POST['username']? $_POST['username'] : '';

					if (!empty($_username)) {
						$_count = db_result(db_query("SELECT COUNT(*) FROM `users` WHERE `name` = '" . db_escape_string($_username) . "' AND `uid` <> " . $user->uid . ";"));
						if ($_count == 0) {
							db_query("UPDATE `users` SET `name` = '" . db_escape_string($_username) . "' WHERE `uid` = " . $user->uid . ";");
							drupal_set_message('Your profile was successfully updated.');
							drupal_goto('user/'.$user->uid.'/account');
						} else {
							drupal_set_message('The username is already taken, please choose another.', 'error');
						}
					} else {
						drupal_set_message('Please enter your username.', 'error');
					}

					break;

				case 9:

					switch ($user->user_type) {

						case 'child':

							$user = ChildUser::castAs($user);

					   	break;

						case 'parent':
						case 'verified-parent':

					   	$user = ParentUser::castAs($user);
					   	$children = $user->getChildren();
					   	foreach ($children as $child) {
								user_delete(array(), $child->uid);
					   	}

					   	break;

						case 'teacher':

							$user = TeacherUser::castAs($user);

					   	break;

					}

					user_delete(array(), $uid);

					drupal_set_message('Your profile was successfully deleted.');
					drupal_goto('');

					break;

			}

		}

		$email = $_POST['email']? $_POST['email'] : $user->mail;
		$first_name = $_POST['first_name']? $_POST['first_name'] : $node->field_first_name[0]['value'];
		$last_name = $_POST['last_name']? $_POST['last_name'] : $node->field_last_name[0]['value'];
		$username = $_POST['username']? $_POST['username'] : $user->name;

		$data->user = $user;
		$data->form->email = $email;
		$data->form->first_name = $first_name;
		$data->form->last_name = $last_name;
		$data->form->username = $username;

		return theme('v2_profiles_account_index', $data);

	}