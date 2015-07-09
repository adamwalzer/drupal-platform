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
			
      v2_profiles_links_myclasses($user, $items);

			//$items[] = (object)array('title' => 'My News', 'href' => '/user/'.$user->uid.'/news');

			if (in_array('can_upload_media', $user->roles)) {
				$items[] = l('My Media', 'user/'.$user->uid.'/videos');
			}

			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = l('My Friends & Requests'.(($count>0)?' <span>'.$count.'</span>':''),  'user/'.$user->uid.'/friends/browse', array('html'=>true));
			}

			if (in_array('can_receive_notices', $user->roles) || in_array('can_receive_notices_via_parent', $user->roles)) {
				//$items['notices'] = (object)array('title' => 'My Notices', 'href' => '/user/'.$user->uid.'/notices');
				$messages_count_all = count(cmwn_notificiations_get_all($uid));
				$messages_count_posting = count(cmwn_notificiations_get_all($uid,cmwn_notifications_posting_notices_subjects()));
				$messages_count_award = count(cmwn_notificiations_get_all($uid,cmwn_notifications_award_notices_subjects()));				
				$messages_count_action = count(cmwn_notificiations_get_all($uid,cmwn_notifications_action_notices_subjects()));				
				$messages_count_account = count(cmwn_notificiations_get_all($uid,cmwn_notifications_account_notices_subjects()));								
								
				$items['notices'] = array(
						'data' => '<a class="toggle my-notices">My Notices'.(($messages_count_all>0)?'<span>'.$messages_count_all.'</span>':'') . '</a>',
						'children' => array(
								l('Posting'.(($messages_count_posting>0)?'<span>'.$messages_count_posting.'</span>':''), 'user/'.$user->uid.'/notices/posting', array('html'=>true)),
								l('Award', 'user/'.$user->uid.'/notices/award'),
								l('Action', 'user/'.$user->uid.'/notices/action'),
								l('Account', 'user/'.$user->uid.'/notices/account'),
							),
					);
			}

			//$items[] = '<a>My Interest Groups</a>';
      $items[] =l('Arcade', 'user/' . $user->uid . '/arcade');

		} else if ($user->user_type == 'parent') {
			$items[] = l('My Profile & Whiteboard', 'user');
			$items[] = l('My Child\'s Profiles', 'user/'.$user->uid.'/children');
			$items[] = l('My Child\'s Permissions', 'user/'.$user->uid.'/children/permissions');


			$children = db_query('select u.uid, u.name from {user_relationships} ur join {users} u on u.uid = ur.requestee_id where requester_id = %d and approved = 1 and rtid = 2', array($user->uid));
			$children_links = array();
			while($child = db_fetch_object($children)){
				$children_links[] = l($child->name, 'user/'.$user->uid.'/notices/child/posting/'.$child->uid);
			}

			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = l('My Friends & Requests'.(($count>0)?' <span>'.$count.'</span>':''),  'user/'.$user->uid.'/friends/browse', array('html'=>true));
			}

			$items['notices'] =array(
					'data' => '<a class="toggle">My Notices</a>',
					'children' => array(
							l('Account', 'user/'.$user->uid.'/notices/account'),
							array(
								'data' => '<a>My Child</a>',
								'children'=>$children_links,

							),

						),
			);

      $items[] = l('Resource Center', 'user/'.$user->uid.'/resources');

			$items[] = array(
				'data'=>l('Add a Child', 'user/'.$user->uid.'/children/add'),
				'class'=>'add-a-child'
			);

		} else {//teacher
			$items[] = l('My Profile', 'user');
			if (in_array('can_make_friends', $user->roles)) {
				$count = v2_profiles_friends_query_requests($user->uid);
				$count = sizeof($count);
				$items[] = l('My Friends & Requests'.(($count>0)?' <span>'.$count.'</span>':''),  'user/'.$user->uid.'/friends/browse', array('html'=>true));
			}

      $school = v2_profiles_school_query($uid);
      
			if ($school) {
				$items[] = l('My School',  'user/'.$user->uid.'/school');
			}

      
      
      v2_profiles_links_myclasses($user, $items);


      if(in_array('School Administrator', ($user->roles))){
        $schools = db_query('select n.nid, n.title from {node} n join {content_field_school_administrator} cfsa on cfsa.nid = n.nid  and cfsa.vid = n.vid join {users} u on u.uid = cfsa.field_school_administrator_uid where u.uid = %d', $user->uid);
        while($school = db_fetch_object($schools)){
          $items[] = l( $school->title . t(' Dashboard'), 'school/'.$school->nid.'/dashboard');            
        }
        //print_r($user);exit();
      }

			

			$items[] = l('My Notices', 'user/'.$user->uid.'/notices/account');
			$items[] = l('Resource Center', 'user/'.$user->uid.'/resources');
			//$items[] = array(
				//'data'=>l('Add a Child', 'user/'.$user->uid.'/children/add'),
				//'class'=>'add-a-child'
			//);

		}

		/*foreach ($items as $item) {

			if ($_SERVER['REQUEST_URI'] === $item->href) $item->active = true;
			else $item->active = false;

		}*/

		return $items;

	}
	


function v2_profiles_links_myclasses($user, &$items){
 //class = if only one class, just link to my class, otherwise submenu.
      $classes = v2_profiles_class_get_profile_classes($user);
      switch(true){
        case (count($classes) == 1):
          $items[] = l('My Class', 'user/'.$user->uid.'/class/' . $classes[0]['nid']);
          break;
          
        case (count($classes) > 1):

          $classes_links = array();
          foreach($classes as $class){
            $class = node_load($class['nid']);
            $classes_links[] = l($class->title,'user/'.$user->uid.'/class/' . $class->nid);
          }

          $items['classes'] =array(
          		'data' => '<a class="toggle">My Classes</a>',
          		'children' => $classes_links,
          );
        
          break;
        
        default:
        
          break;
      } 
}
