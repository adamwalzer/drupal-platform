<?php

	/* 1.4 */

	$v2_profiles_menu_items['user/%/links'] = array(	
		'access arguments' => array(1),
		'access callback' => 'v2_profiles_access',
		'description' => '',
		'page arguments' => array(1),
		'page callback' => 'v2_profiles_links_index',
		'title' => 'Links',
		'type' => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_links_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/links/index'
	);

	function v2_profiles_links_index($uid) {

		$data = new stdClass();

		$user = user_load($uid);

		$tids = array();
		if ($user->user_type == 'child') {
			$child = ChildUser::castAs($user);
			if ($child) {
				foreach ($child->getChildProfile()->taxonomy as $term) {
					$tids[] = $term->tid;
				}
			}
		}

		$interests = array();
		$terms = taxonomy_get_tree(3);
		foreach ($terms as $term) {
			$interest = new stdClass();
			$interest->class = 'id-'.str_pad($term->tid,3,'0',STR_PAD_LEFT).((in_array($term->tid,$tids))?' active':'');
			$interest->href = '/user/'.$uid.'/friends/search/'.$term->tid;
			$interest->title = $term->name;
			$interests[] = $interest;
		}

		$items = v2_profiles_links_query_all($uid);

		$data->interests = $interests;
		$data->items = $items;

		return theme('v2_profiles_links_index', $data);

	}

	function v2_profiles_links_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if ($user->user_type == 'child') {

			$items[] = (object)array('title' => 'My Profile &amp; Whiteboard', 'href' => '/user');

			$school = v2_profiles_school_query($uid);

			if ($school) {
				$items[] = (object)array('title' => 'My School', 'href' => '/user/'.$user->uid.'/school');
			}

			//$items[] = (object)array('title' => 'My News', 'href' => '/user/'.$user->uid.'/news');

			if (in_array('can_upload_media', $user->roles)) {
				$items[] = (object)array('title' => 'My Videos', 'href' => '/user/'.$user->uid.'/videos');
			}

			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = (object)array('title' => 'My Friends &amp; Requests'.(($count>0)?' <span>'.$count.'</span>':''), 'href' => '/user/'.$user->uid.'/friends/browse');
			}

			if (in_array('can_receive_notices', $user->roles) || in_array('can_receive_notices_via_parent', $user->roles)) {
				$items[] = (object)array('title' => 'My Notices', 'href' => '/user/'.$user->uid.'/notices');
			}

			$items[] = (object)array('title' => 'My Interest Groups', 'href' => '#');

		} else if ($user->user_type == 'parent') {

			$items[] = (object)array('title' => 'My News', 'href' => '/user');
			$items[] = (object)array('title' => 'My Children\'s Profiles', 'href' => '/user/'.$user->uid.'/children');
			$items[] = (object)array('title' => 'My Children\'s Permissions', 'href' => '/user/'.$user->uid.'/children/permissions');
			$items[] = (object)array('title' => 'Add a Child', 'href' => '/user/'.$user->uid.'/children/add');

		} else {

			$items[] = (object)array('title' => 'My News', 'href' => '/user');

		}

		foreach ($items as $item) {

			if ($_SERVER['REQUEST_URI'] === $item->href) $item->active = true;
			else $item->active = false;

		}

		return $items;

	}