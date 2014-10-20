<?php

	function cmwn_module_base_profile_node_form(&$form, &$form_state) {

		global $user;

		$form['title']['#access'] = false;
		$form['menu']['#access'] = false;
		$form['path']['#access'] = false;
		$form['comment_settings']['#access'] = false;
		$form['revision_information']['#access'] = false;
		$form['buttons']['preview']['#access'] = false;
		$form['options']['promote']['#access'] = false;
		$form['options']['sticky']['#access'] = false;

		if (!in_array('administrator', $user->roles)) {
			$form['field_avatar_reference']['#access'] = false;
		}

		//if (isset($form_state['storage']['register']) && (!$form_state['storage']['register'] || !(in_array('administrator', $user->roles)))) {
		//  $form['field_first_name']['#access'] = false;
		//  $form['field_last_name']['#access'] = false;
		//}

	}

	function cmwn_module_base_profile_node_form_validate($form, &$form_state) {

	}

	function cmwn_module_base_profile_node_form_submit($form, $form_state) {

	}

	function cmwn_module_base_profile_user_register(&$form, &$form_state) {

		$form['#content_profile_registration_use_types']['base_profile'] = 'Base Profile';
		$form['#validate'][] = 'cmwn_module_base_profile_user_register_validate';
		$form['#submit'][] = 'cmwn_module_base_profile_user_register_submit';

	}

	function cmwn_module_base_profile_user_register_validate($form, &$form_state) {

	}

	function cmwn_module_base_profile_user_register_submit($form, $form_state) {

	}