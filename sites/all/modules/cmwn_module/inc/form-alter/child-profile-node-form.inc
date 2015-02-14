<?php

	function cmwn_module_child_profile_node_form(&$form, &$form_state) {

		global $user;

		if (!user_access('assign child to school') && $user->uid > 0) {
			$form['field_school']['#access'] = false;
		} else if ($user->uid == 0) {
			$form['field_school']['#type'] = 'value';
		}

		$form['title']['#access'] = false;
		$form['menu']['#access'] = false;
		$form['path']['#access'] = false;
		$form['comment_settings']['#access'] = false;
		$form['revision_information']['#access'] = false;
		$form['buttons']['preview']['#access'] = false;
		$form['options']['promote']['#access'] = false;
		$form['options']['sticky']['#access'] = false;
		$form['field_country']['#access'] = false;

		if (!user_access('award children badges')) {
			unset($form['field_badges']);
		}

		if (!$form_state['storage']['register'] && !(in_array('administrator', $user->roles))) {
			$form['field_state']['#type'] = 'value';
		}

		if (!(in_array('administrator', $user->roles) || $form_state['storage']['register'])) {
			unset($form['field_dob']);
		}

	}

	function cmwn_module_child_profile_node_form_validate($form, &$form_state) {
		
	}

	function cmwn_module_child_profile_node_form_submit($form, $form_state) {
		
	}

	function cmwn_module_child_profile_user_register(&$form, &$form_state) {

		$form['#content_profile_registration_use_types']['child_profile'] = 'Child Profile';
		$form['#validate'][] = 'cmwn_module_child_profile_user_register_validate';
		$form['#submit'][] = 'cmwn_module_child_profile_user_register_submit';

		$form['name']['#description'] = 'Your username must be between 4-12 letters, and you can use numbers or spaces. DO NOT use your real name.';
		$form['pass']['#description'] = 'Your password should be easy to remember but difficult to guess. It must be between 4-12 letters, and you can use numbers or spaces.';
		$form['mail']['#description'] = 'Please enter your email address. If you don\'t have one, you can use your parent\'s email address for your account.';

		$form['parent_email'] = array(
			'#description' => 'We need your parent\'s email address so we can get their approval. (If they don\'t see it immediately, ask them to check their SPAM or BULK MAIL folder)',
			'#required' => true,
			'#title' => 'Parent\'s Email Address',
			'#type' => 'textfield',
		);

		$form['school_code'] = array(
			'#description' => 'If you received a postcard from your teacher or administrator, your school code is located there. If you didn\'t leave this field blank.',
			'#title' => 'School Code',
			'#type' => 'textfield',
		);

		$form['terms_and_conditions'] = array(
			'#description' => 'Terms of Use and Privacy Policy',
			'#required' => true,
			'#title' => 'I agree to Terms of Use and Privacy Policy',
			'#type' => 'checkbox',
		);

		$form['gender'] = array(
			'#options' => array(
				'boy' => 'Boy',
				'girl' => 'Girl',
			),
			'#required' => true,
			'#title' => '',
			'#type' => 'radios',
		);

		$form['field_school']['#access'] = false;
		$form_state['storage']['register'] = true;

	}

	function cmwn_module_child_profile_user_register_validate($form, &$form_state) {

		$node = $form_state['content_profile_registration']['base_profile']['node'];
		$firstname = $node->field_first_name[0]['value'];
		$lastname = $node->field_last_name[0]['value'];
		$username = $form_state['values']['name'];
		$email = $form_state['values']['mail'];
		$parent_email = $form_state['values']['parent_email'];
		$school_code = $form_state['values']['school_code'];
		$terms_and_conditions = $form_state['values']['terms_and_conditions'];
		$gender = $form_state['values']['gender'];

		if (stripos($username, $firstname) !== false) {
			form_set_error('name', 'Please do not include your real name in your username.');
		}

		if (stripos($username, $lastname) !== false) {
			form_set_error('name', 'Please do not include your real name in your username.');
		}

		if (!$parent_email) {
			form_set_error('parent_email', 'Please enter a valid email address.');
		}

		if ($parent_email == $email) {
			form_set_error('parent_email', 'Your parent\'s email address must not be the same as yours.');
		}

		if (function_exists('email_verify_check') && $error = email_verify_check($parent_email)) {
			form_set_error('parent_email', $error);
		}

		if (!valid_email_address($parent_email)) {
			form_set_error('parent_email', 'Please enter a valid email address.');
		}

		if ($school_code && !empty($school_code)) {
			if (!get_school_nid_by_code($school_code)) {
				form_set_error('school_code', 'The school code you entered is not valid.');
			}
		}

		if (!$gender || empty($gender)) {
			form_set_error('gender', 'Please select your gender.');
		}

		if (!$terms_and_conditions || empty($terms_and_conditions) || $terms_and_conditions == '0') {
			form_set_error('terms_and_conditions', 'You must agree to terms and conditions.');
		}

	}

	function cmwn_module_child_profile_user_register_submit($form, &$form_state) {

		$nid = get_school_nid_by_code($form_state['values']['school_code']);

		if ($nid) {
			$form_state['content_profile_registration']['child_profile']['node']->field_school = array(array('nid' => $nid));
			node_save($form_state['content_profile_registration']['child_profile']['node']);
		}

		drupal_goto('node/454');

	}