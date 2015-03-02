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

	/*function v2_profiles_links_query_all($uid) {

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
				$items[] = (object)array('title' => 'My Media', 'href' => '/user/'.$user->uid.'/videos');
			}

			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = (object)array('title' => 'My Friends &amp; Requests'.(($count>0)?' <span>'.$count.'</span>':''), 'href' => '/user/'.$user->uid.'/friends/browse');
			}

			if (in_array('can_receive_notices', $user->roles) || in_array('can_receive_notices_via_parent', $user->roles)) {
				//$items['notices'] = (object)array('title' => 'My Notices', 'href' => '/user/'.$user->uid.'/notices');
				$items['notices'] = (object)array('title' => 'My Notices', 'href' => '#');
				$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Posting', 'href' => '/user/'.$user->uid.'/notices/posting');
				$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Award', 'href' => '/user/'.$user->uid.'/notices/award');
				$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Action', 'href' => '/user/'.$user->uid.'/notices/action');
				$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Account', 'href' => '/user/'.$user->uid.'/notices/account');
			}

			$items[] = (object)array('title' => 'My Interest Groups', 'href' => '#');
      $items[] = (object)array('title' => 'Arcade', 'href' => '/node/13120');

		} else if ($user->user_type == 'parent') {
			$items[] = (object)array('title' => 'My Profile &amp; Whiteboard', 'href' => '/user');
			//$items[] = (object)array('title' => 'My News', 'href' => '/user');
			$items[] = (object)array('title' => 'My Child\'s Profiles', 'href' => '/user/'.$user->uid.'/children');
			$items[] = (object)array('title' => 'My Child\'s Permissions', 'href' => '/user/'.$user->uid.'/children/permissions');


			$items['notices'] = (object)array('title' => 'My Notices', 'href' => '#');
			$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Account', 'href' => '/user/'.$user->uid.'/notices/account');

			//list children, show custom link to children's messages
			$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;My Child', 'href' => '#');

			$children = db_query('select u.uid, u.name from {user_relationships} ur join {users} u on u.uid = ur.requestee_id where requester_id = %d and approved = 1 and rtid = 2', array($user->uid));

			while($child = db_fetch_object($children)){
  			$items[] = (object)array('title' => '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;' . $child->name, 'href' => '/user/'.$user->uid.'/notices/child/posting/'.$child->uid);
			}


			$items[] = (object)array('title' => 'Add a Child', 'href' => '/user/'.$user->uid.'/children/add');

		} else {

			$items[] = (object)array('title' => 'My News', 'href' => '/user');

		}

		foreach ($items as $item) {

			if ($_SERVER['REQUEST_URI'] === $item->href) $item->active = true;
			else $item->active = false;

		}

		return $items;

	}*/


	function v2_profiles_links_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if ($user->user_type == 'child') {

			$items[] = l('My Profile & Whiteboard', 'user');

			$school = v2_profiles_school_query($uid);

			if ($school) {
				$items[] = l('My School',  'user/'.$user->uid.'/school');
			}

			//$items[] = (object)array('title' => 'My News', 'href' => '/user/'.$user->uid.'/news');

			if (in_array('can_upload_media', $user->roles)) {
				$items[] = l('My Media', 'user/'.$user->uid.'/videos');
			}

			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = l('My Friends &amp; Requests'.(($count>0)?' <span>'.$count.'</span>':''),  'user/'.$user->uid.'/friends/browse');
			}

			if (in_array('can_receive_notices', $user->roles) || in_array('can_receive_notices_via_parent', $user->roles)) {
				//$items['notices'] = (object)array('title' => 'My Notices', 'href' => '/user/'.$user->uid.'/notices');
				$items['notices'] = array(
						'data' => 'My Notices',
						'children' => array(
								l('Posting', 'user/'.$user->uid.'/notices/posting'),
								l('Award', 'user/'.$user->uid.'/notices/award'),
								l('Action', 'user/'.$user->uid.'/notices/action'),
								l('Account', 'user/'.$user->uid.'/notices/account'),
							),
					);
			}

			$items[] = 'My Interest Groups';
      $items[] =l('Arcade', 'node/13120');

		} else if ($user->user_type == 'parent') {
			$items[] = l('My Profile & Whiteboard', 'user');
			$items[] = l('My Child\'s Profiles', 'user/'.$user->uid.'/children');
			$items[] = l('My Child\'s Permissions', 'user/'.$user->uid.'/children/permissions');


			$children = db_query('select u.uid, u.name from {user_relationships} ur join {users} u on u.uid = ur.requestee_id where requester_id = %d and approved = 1 and rtid = 2', array($user->uid));
			$children_links = array();
			while($child = db_fetch_object($children)){
				$children_links[] = l($child->name, 'user/'.$user->uid.'/notices/child/posting/'.$child->uid);
			}


			$items['notices'] =array(
					'data' => '<a>My Notices</a>',
					'children' => array(
							l('Account', 'user/'.$user->uid.'/notices/account'),
							array(
								'data' => '<a>My Child</a>',
								'children'=>$children_links,
							),

						),
			);


			$items[] = array(
				'data'=>l('Add a Child', 'user/'.$user->uid.'/children/add'),
				'class'=>'add-a-child'
			);

		} else {

			$items[] = l('My News', 'user');

		}

		/*foreach ($items as $item) {

			if ($_SERVER['REQUEST_URI'] === $item->href) $item->active = true;
			else $item->active = false;

		}*/

		return $items;

	}
