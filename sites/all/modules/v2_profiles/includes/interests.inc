<?php

	/* 1.4 */

	$v2_profiles_theme_items['v2_profiles_interests_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/interests/index'
	);

	function v2_profiles_interests_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$all = v2_profiles_interests_query_all($uid);
		$active = array();

		foreach ($all as $key => $value) {
			if ($value->active == 1) {
				$active[] = $value;
			}
		}

		$data->items->all = $all;
		$data->items->active = $active;
		$data->user = $user;

		return theme('v2_profiles_interests_index', $data);

	}

	function v2_profiles_interests_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$tids = array();
		if ($user->user_type == 'child') {
			$child = ChildUser::castAs($user);
			if ($child) {
				foreach ($child->getChildProfile()->taxonomy as $term) {
					$tids[] = $term->tid;
				}
			}
		}

		$terms = taxonomy_get_tree(3);
		foreach ($terms as $term) {
			$interest = new stdClass();
			$interest->active = in_array($term->tid,$tids)?1:0;
			$interest->id = $term->tid;
			$interest->title = $term->name;
			$items[] = $interest;
		}

		return $items;

	}