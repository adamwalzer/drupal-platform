<?php

	function cmwn_module_parent_profile_node_form(&$form, &$form_state) {

		$form['title']['#access'] = false;
		$form['menu']['#access'] = false;
		$form['path']['#access'] = false;
		$form['comment_settings']['#access'] = false;
		$form['revision_information']['#access'] = false;
		$form['buttons']['preview']['#access'] = false;
		$form['options']['promote']['#access'] = false;
		$form['options']['sticky']['#access'] = false;
		$form['#validate'][] = 'cmwn_module_parent_profile_node_form_validate';
		$form['#submit'][] = 'cmwn_module_parent_profile_node_form_submit';

	}

	function cmwn_module_parent_profile_node_form_validate($form, &$form_state) {

	}

	function cmwn_module_parent_profile_node_form_submit($form, $form_state) {

	}

	function cmwn_module_parent_profile_user_register(&$form, &$form_state) {

		$form['#content_profile_registration_use_types']['parent_profile'] = 'Parent Profile';
		$form['#validate'][] = 'cmwn_module_parent_profile_user_register_validate';
		$form['#submit'][] = 'cmwn_module_parent_profile_user_register_submit';

		$form['terms_and_conditions'] = array(
			'#description' => 'Terms of Use and Privacy Policy',
			'#required' => true,
			'#title' => 'I agree to Terms of Use and Privacy Policy',
			'#type' => 'checkbox',
		);

		if (arg(3)) {
			if ($token = get_parent_registration_token(arg(3))) {
				$form['parental_consent_token'] = array(
					'#type' => 'value',
					'#value' => $token
				);
				$child = user_load($token['cuid']);
				if ($child && isset($child->parent_email)) {
					$form['mail']['#type'] = 'value';
					$form['mail']['#value'] = $child->parent_email;
				}
			} else {
				drupal_set_message(t("Problem with token"), 'error');
				$form['parental_consent_token'] = array(
					'#type' => 'value',
					'#value' => false
				);
			}
		}

	}

	function cmwn_module_parent_profile_user_register_validate($form, &$form_state) {

		$parental_consent_token = $form_state['values']['parental_consent_token'];
		$terms_and_conditions = $form_state['values']['terms_and_conditions'];

		if ($parental_consent_token === false) {
			drupal_set_message('Unable to register with supplied token', 'error');
			form_set_error('', '');
		}

		if (!$terms_and_conditions || empty($terms_and_conditions) || $terms_and_conditions == '0') {
			form_set_error('terms_and_conditions', 'You must agree to terms and conditions.');
		}

	}

	function cmwn_module_parent_profile_user_register_submit($form, $form_state) {

		drupal_goto('node/11186');

	}

	function _cmwn_module_add_parent_child_relationship($parent, $child) {

		$token = ChildUser::castAs($child)->getParentalConsentToken();

		if ($token) {

			$token['puid'] = $parent->uid;
			$token['puip'] = ip2long($_SERVER['REMOTE_ADDR']);
			drupal_write_record('cmwn_parental_consent_token', $token, array('cuid'));
			user_relationships_request_relationship($parent, $child, 2, true); // Parent
			user_relationships_request_relationship($child, $parent, 3, true); // Child
			$roles = user_roles();
			//$index = variable_get('cmwn_module_approved_child_role', '');
			//if ($index) {
			//  $child->roles[$index] = $roles[$index];
			//  user_save($child, array('roles' => $child->roles));
			//}

		}

	}