<?php

	function cmwn_module_user_register(&$form, &$form_state) {

		// Determine desired user type
		$path = drupal_get_path('module', 'cmwn_module');
		if (!arg(2)) {
			drupal_goto('user/register/'.get_role_from_rid(variable_get('cmwn_module_child_role', '')));
		}
		$child_role = get_role_from_rid(variable_get('cmwn_module_child_role', ''));
		$parent_role = get_role_from_rid(variable_get('cmwn_module_parent_role', ''));
		$teacher_role = get_role_from_rid(variable_get('cmwn_module_teacher_role', ''));
		switch (arg(2)) {
			case $child_role:
				$user_type = $child_role;
				break;
			case $parent_role:
				$user_type = $parent_role;
				break;
			case $teacher_role:
				$user_type = $teacher_role;
				break;
		}
		$form['user_type'] = array(
			'#type' => 'value',
			'#value' => $user_type
		);
		
		// Global form callbacks
		$form['#validate'][] = 'cmwn_module_user_register_validate';
		$form['#submit'][] = 'cmwn_module_user_register_submit';
		
		// Initialize list of content profile types to use
		$form['#content_profile_registration_use_types'] = array();
		
		// Add base profile content profile
		require_once $path.'/inc/form-alter/base-profile-node-form.inc';
		cmwn_module_base_profile_user_register($form, $form_state);

		$form['field_first_name'][0]['#description'] = 'Please enter your first name.';
		$form['field_first_name'][0]['#title'] = 'Your First Name';

		$form['field_last_name'][0]['#description'] = 'Please enter your last name.';
		$form['field_last_name'][0]['#title'] = 'Your Last Name';

		$form['name']['#description'] = 'Your username must be between 4-12 letters, and you can use numbers or spaces.';
		$form['name']['#title'] = 'Create Your Username';

		$form['pass']['#description'] = 'Your password must be between 4-12 letters, and you can use numbers or spaces.';

		$form['mail']['#description'] = 'A valid email address is needed for confirmation.';
		$form['mail']['#title'] = 'Your Email Address';

		//$form['field_state']['#description'] = '';
		//$form['field_state']['#title'] = '';

		// Allow forms for different user types to take actions on the entire form.
		switch ($user_type) {
			case $child_role:
				require_once $path.'/inc/form-alter/child-profile-node-form.inc';
				cmwn_module_child_profile_user_register($form, $form_state);
				break;
			case $parent_role:
				require_once $path.'/inc/form-alter/parent-profile-node-form.inc';
				cmwn_module_parent_profile_user_register($form, $form_state);
				break;
			case $teacher_role:
				require_once $path.'/inc/form-alter/teacher-profile-node-form.inc';
				cmwn_module_teacher_profile_user_register($form, $form_state);
				break;
		}
		
		// Add appropriate content profile node forms
		foreach ($form['#content_profile_registration_use_types'] as $type => $typename) {
			content_profile_registration_add_profile_form($type, $form, $form_state);
		}

		$form['field_phone'][0]['#description'] = 'A phone number is not required for membership. If you provide one, it may be used for customer service or administrative purposes for your account.';

	}

	function cmwn_module_user_register_validate($form, &$form_state) {
		
	}

	function cmwn_module_user_register_submit($form, &$form_state) {

		global $user;

		$parent_role = get_role_from_rid(variable_get('cmwn_module_parent_role', ''));
		//$teacher_role = get_role_from_rid(variable_get('cmwn_module_teacher_role', ''));

		if (in_array($parent_role, $user->roles)/* || in_array($teacher_role, $user->roles)*/) {
		//  $form_state['redirect'] = 'user/'.$user->uid.'/confirm-identity';
		//} else {
			$form_state['redirect'] = '';
		}

	}