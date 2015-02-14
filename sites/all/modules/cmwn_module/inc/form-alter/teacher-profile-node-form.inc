<?php

	function cmwn_module_teacher_profile_node_form(&$form, &$form_state) {

		$form['title']['#access'] = false;
		$form['menu']['#access'] = false;
		$form['path']['#access'] = false;
		$form['comment_settings']['#access'] = false;
		$form['revision_information']['#access'] = false;
		$form['buttons']['preview']['#access'] = false;
		$form['options']['promote']['#access'] = false;
		$form['options']['sticky']['#access'] = false;

	}

	function cmwn_module_teacher_profile_node_form_validate($form, &$form_state) {

	}

	function cmwn_module_teacher_profile_node_form_submit($form, $form_state) {

	}

	function cmwn_module_teacher_profile_user_register(&$form, &$form_state) {

		$form['#content_profile_registration_use_types']['teacher_profile'] = 'Teacher Profile';
		$form['#validate'][] = 'cmwn_module_teacher_profile_node_form_validate';
		$form['#submit'][] = 'cmwn_module_teacher_profile_user_register_submit';

		$form['terms_and_conditions'] = array(
			'#description' => 'Terms of Use and Privacy Policy',
			'#required' => true,
			'#title' => 'I agree to Terms of Use and Privacy Policy',
			'#type' => 'checkbox',
		);

	}

	function cmwn_module_teacher_profile_user_register_validate($form, &$form_state) {

		$terms_and_conditions = $form_state['values']['terms_and_conditions'];

		if (!$terms_and_conditions || empty($terms_and_conditions) || $terms_and_conditions == '0') {
			form_set_error('terms_and_conditions', 'You must agree to terms and conditions.');
		}

	}

	function cmwn_module_teacher_profile_user_register_submit($form, $form_state) {

		drupal_goto('node/12732');

	}