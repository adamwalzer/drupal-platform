<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/register/child/2/confirmation'] = array(	
		'access arguments' => array(),
		'access callback' => 'v2_profiles_authenticated_access',
		'description' => '',
		'page arguments' => array(),
		'page callback' => 'v2_profiles_register_2_confirmation',
		'title' => 'Register',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_register_2_confirmation'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/register/confirmation'
	);

	function v2_profiles_register_2_confirmation() {

		global $user;

		$data = new stdClass();

		$child = ChildUser::castAs($user);
		$node = $child->getChildProfile();
		$taxonomy = $node->taxonomy;
		$terms = taxonomy_get_tree(3);

		$items = array();

		foreach ($terms as $term) {
			$item = new stdClass();
			$item->class = 'id-'.str_pad($term->tid,3,'0',STR_PAD_LEFT).((in_array($term->tid, array_keys($taxonomy)))?' active':'');
			$item->title = $term->name;
			$items[] = $item;
		}

		$data->items = $items;

		return theme('v2_profiles_register_2_confirmation', $data);

	}