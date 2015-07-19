<?php

function cmwn_preprocess(&$vars, $hook) {
	// In D6, the page.tpl uses a different variable name to hold the classes.
	$key = ($hook == 'page' || $hook == 'maintenance_page') ? 'body_classes' : 'classes';

	// Create a D7-standard classes_array variable.
	if (array_key_exists($key, $vars)) {
		// Views (and possibly other modules) have templates with a $classes
		// variable that isn't a string, so we leave those variables alone.
		if (is_string($vars[$key])) {
			$vars['classes_array'] = explode(' ', $hook . ' ' . $vars[$key]);
			unset($vars[$key]);
		}
	}
	else {
		$vars['classes_array'] = array($hook);
	}
	$vars['theme_path'] = base_path().drupal_get_path('theme', 'cmwn');
	//print_r($vars['template_files']);
}

function cmwn_preprocess_page(&$vars) {
	global $user;
	if (ParentUser::canHydrate($user)) {
		$parent = ParentUser::castAs($user);
		if (!in_array(get_role_from_rid(variable_get('cmwn_module_verified_parent_role', '')), array_values(ParentUser::castAs($user)->roles))) {
			if (!(arg(0) == 'user' && arg(2) == 'confirm-identity')) {
				$vars['overlay'] = theme('cmwn_parent_reminder_overlay');
			}
		} else if ($_SESSION['parent_child_perms_reminder']) {
			unset($_SESSION['parent_child_perms_reminder']);
			$vars['overlay'] = theme('cmwn_parent_child_perms_reminder_overlay');
		}
	}
	$nid = variable_get('cmwn_survey_interest_survey_nid', '');
	if (!(arg(0) == 'node' && arg(1) == $nid) && ChildUser::canHydrate($user)) {
  	$child = ChildUser::castAs($user);
    @$schools = array_filter(ChildUser::castAs($user)->getSchools());
    //$schools = array();
		if (!$child->hasCompletedInterestSurvey() && empty($schools)) {
			//drupal_set_message(t("Don't forget to <a href=\"!url\">complete your interest survey!</a>", array('!url' => url('node/'.$nid))));
			$vars['overlay'] = theme('user-register-child-step2-reminder');
		}
	}
	if (arg(0) == 'user' && arg(1) == 'register' && arg(2) == 'parent' && arg(3) && !arg(4)) {
		$_SESSION['parent_token'] = arg(3);
		drupal_goto('');
	}
	if ($_SESSION['parent_token']) {
		$result = db_fetch_object(db_query("SELECT puid FROM {cmwn_parental_consent_token} WHERE token = '%s'",$_SESSION['parent_token']));
		if ($result && $result->puid > 0) {
			$vars['overlay'] = theme('user-register-account-exists');
		} else {
			$vars['overlay'] = theme('user-register-parent-step1-reminder');
		}
	}
	$patterns = <<<EOP
admin/build/views/edit*
admin/content/node-type/*
*webform*
EOP;

//$scripts = drupal_add_js();
//dsm($scripts);
	if (!drupal_match_path($_GET['q'], $patterns)) {
		$scripts = drupal_add_js();
		/*$scripts['core'] = array_merge(array(
			drupal_get_path('theme', 'cmwn').'/assets/js/jquery.tools.min.js' => array(
				'cache' => true,
				'defer' => false,
				'preprocess' => true
			)
		), $scripts['core']);*/

		//remove old core jquery for front-end-non-views-drupal-core pages
		unset($scripts['core']['misc/jquery.js']);

		//add our updated jquery;
		$scripts['core'] = array_merge(array(
			//'sites/all/themes/cmwn/assets/js/jquery.min.js' => array(
			'sites/all/themes/cmwn/assets/js/jquery-1.4.4.min.js' => array(
				'cache' => true,
				'defer' => false,
				'preprocess' => true
			)
		), $scripts['core']);

		$vars['scripts'] = drupal_get_js('header', $scripts);
	}else{//not a core drupal js page

		$scripts = drupal_add_js();

		//remove old core jquery so we can update to newer one.
		unset($scripts['core']['misc/jquery.js']);

		//update to 1.3.2 for regular drupal core/views page.
		$scripts['core'] = array_merge(array(
			'sites/all/themes/cmwn/assets/js/jquery-1.3.2.min.js' => array(
				'cache' => true,
				'defer' => false,
				'preprocess' => true
			)
		), $scripts['core']);

		$vars['scripts'] = drupal_get_js('header', $scripts);

	}
	if ($vars['is_front']) {
		$vars['campaign'] = views_embed_view('homepage_slideshow', 'default');
		$vars['skin_class'] = 'home-wrap';
	} else if (arg(0) == 'admin') {
		$vars['skin_class'] = 'admin-wrap';
	} else {
		$vars['skin_class'] = 'interior-wrap';
	}
	//$primary_links = menu_tree_build(array(
	//  'menu_name' => 'primary-links',
	//  'depth' => 1
	//));
	$vars['primary_links'] = theme('cmwn_primary_links');
	$vars['secondary_links'] = menu_tree('secondary-links');
	$vars['footer_links'] = menu_tree('menu-footer-links');
	$vars['footer_utilities'] = menu_tree('menu-footer-utilities');
	$search = module_invoke('search', 'block', 'view');
	if (is_array($search) && isset($search['content'])) {
		$vars['search'] = $search['content'];
	}
	if ($user->uid == 0) {
		$vars['login'] = l('Login', 'user/login', array('attributes' => array('class' => 'login')));
		$vars['login'] .= l('Create A Profile', 'register-choose', array('attributes' => array('class' => 'register')));
	} else {
		$vars['login'] = l('Logout', 'logout', array('attributes' => array('class' => 'logout')));
		$vars['login'] .= l('My Profile', 'user', array('attributes' => array('class' => 'my-profile')));
	}
	if ($vars['node']) {
		$temp = array_pop($vars['template_files']);
		$vars['template_files'][] = 'page-node-'.$vars['node']->type;
		$vars['template_files'][] = $temp;
		if ($vars['node']->type == 'article') {
			$vars['template_files'][] = 'page-node-landing_page';
		}
	}
	/* v2_profiles */
	if ($router = menu_get_item($path)) {
		if ($user->uid > 0 && $router['access'] && $router['access'] == 1) {
			if (
				!in_array('page-user-register', $vars['template_files']) &&
				!in_array('page-user-login', $vars['template_files']) &&
				!in_array('page-user-confirm-identity', $vars['template_files'])
			) {
				foreach (array('page-user') as $template) {
					if (in_array($template,$vars['template_files'])) {
						$vars['template_files'][] = 'v2-page-user';
					}
				}
			}
			if ($vars['node'] && $vars['node']->type == 'base_profile' && arg(2) && arg(2) == 'edit') {
				$vars['template_files'][] = 'v2-page-user';
			}
		}
	}
	//print(arg());print_r($vars['template_files']);
}

function cmwn_preprocess_block(&$vars, $hook) {
	// Special classes for blocks.
	$vars['classes_array'][] = 'block-' . $vars['block']->module;
	// Classes describing the position of the block within the region.
	if ($vars['block_id'] == 1) {
		$vars['classes_array'][] = 'first';
	}
	if (!function_exists('context_blocks') && count(block_list($vars['block']->region)) == $vars['block_id']) {
		$vars['classes_array'][] = 'last';
	}

	// Create the block ID.
	$vars['block_html_id'] = 'block-' . $vars['block']->module . '-' . $vars['block']->delta;
}

function cmwn_preprocess_node(&$vars, $hook) {
	global $user;
	// Create the build_mode variable.
	$vars['template_files'][] = 'node-'.$vars['node']->type;
	$vars['template_files'][] = 'node-'.$vars['node']->nid;
	switch ($vars['node']->build_mode) {
		case NODE_BUILD_NORMAL:
			if ($vars['node']->build_mode === NODE_BUILD_NORMAL) {
				$vars['build_mode'] = $vars['teaser'] ? 'teaser' : 'full';
			}
			else {
				$vars['build_mode'] = $vars['node']->build_mode;
			}
			$dest = drupal_get_destination();
			$node = $vars['node'];
			if ($vars['node']->type == 'project') {
				if (!og_is_group_member($vars['node']->nid) && in_array(get_role_from_rid(variable_get('cmwn_module_approved_child_role', '')), array_values($user->roles))) {
					drupal_set_message(t('<a href="!url">Join</a> this project!', array('!url' => url("og/subscribe/$node->nid", array('query' => $dest)))));
				}
			}
			break;
		case NODE_BUILD_PREVIEW:
			$vars['build_mode'] = 'preview';
			break;
		case NODE_BUILD_SEARCH_INDEX:
			$vars['build_mode'] = 'search_index';
			break;
		case NODE_BUILD_SEARCH_RESULT:
			$vars['build_mode'] = 'search_result';
			break;
		case NODE_BUILD_RSS:
			$vars['build_mode'] = 'rss';
			break;
		case NODE_BUILD_PRINT:
			$vars['build_mode'] = 'print';
			break;
		default:
			$vars['build_mode'] = $vars['node']->build_mode;
	}

	// Special classes for nodes.
	// Class for node type: "node-type-page", "node-type-story", "node-type-my-custom-type", etc.
	$vars['classes_array'][] = drupal_html_class('node-type-' . $vars['type']);
	if ($vars['promote']) {
		$vars['classes_array'][] = 'node-promoted';
	}
	if ($vars['sticky']) {
		$vars['classes_array'][] = 'node-sticky';
	}
	if (!$vars['status']) {
		$vars['classes_array'][] = 'node-unpublished';
		$vars['unpublished'] = TRUE;
	}
	else {
		$vars['unpublished'] = FALSE;
	}
	if ($vars['uid'] && $vars['uid'] == $GLOBALS['user']->uid) {
		$vars['classes_array'][] = 'node-by-viewer'; // Node is authored by current user.
	}
	if ($vars['teaser']) {
		$vars['classes_array'][] = 'node-teaser'; // Node is displayed as teaser.
	}
	if (isset($vars['preview'])) {
		$vars['classes_array'][] = 'node-preview';
	}
	$vars['classes_array'][] = 'build-mode-' . $vars['build_mode'] ;
	switch ($vars['type']) {
		case 'forum':
			$vars['submitted'] = cmwn_node_submitted($vars['node']);
			$author = user_load($vars['uid']);
			$author = GenericUser::castAs($author);
			$avatar = $author->getAvatar(true);
			$vars['picture'] = $avatar;
	}
	//print(arg());print_r($vars['template_files']);
}

function cmwn_preprocess_user_register(&$vars) {
	global $user;
	if (in_array('administrator', $user->roles)) {
		$vars['template_files'][] = 'user-register-admin';
	} else {
		$type = $vars['form']['user_type']['#value'];
		if ($type) {
			$vars['template_files'][] = 'user-register-'.preg_replace('/[^a-zA-Z0-9_-]+/', '-', $type);
		}
	}
}

function cmwn_preprocess_search_block_form(&$vars) {
	//$vars['search_form']
	//var_dump($vars);die;
}

function cmwn_preprocess_forums(&$vars) {
	//var_dump($projects);die;
	$vid = variable_get('forum_nav_vocabulary', '');
	$vocabulary = taxonomy_vocabulary_load($vid);
	$title = !empty($vocabulary->name) ? $vocabulary->name : '';

	// Breadcrumb navigation:
	$breadcrumb[] = l(t('Home'), NULL);
	if ($vars['parents']) {
		$vars['parents'] = array_reverse($vars['parents']);
		foreach ($vars['parents'] as $p) {
			if ($p->tid == $vars['tid']) {
				$title = $p->name;
			}
			else {
				$breadcrumb[] = l($p->name, 'forum/'. $p->tid);
			}
		}
	}
	drupal_set_breadcrumb($breadcrumb);
}

function cmwn_preprocess_forum_list(&$vars) {

	$vars['template_files'][] = 'forum-list-'.$vars['forum_id'];
}

function cmwn_preprocess_comment(&$vars) {
	$author = user_load($vars['comment']->uid);
	$author = GenericUser::castAs($author);
	$avatar = $author->getAvatar(true);
	$vars['picture'] = $vars['comment']->picture = $avatar;
	$vars['submitted'] = cmwn_comment_submitted($vars['comment']);
}

function cmwn_preprocess_forum_topic_list(&$vars) {
	//var_dump($vars);die;
	global $forum_topic_list_header;
	//var_dump($forum_topic_list_header);die;
	// Create the tablesorting header.
	$ts = tablesort_init($forum_topic_list_header);
	$header = '';
	array_shift($forum_topic_list_header);
	foreach ($forum_topic_list_header as $cell) {
		$cell = cmwn_tablesort_header($cell, $forum_topic_list_header, $ts);
		$header .= _theme_table_cell($cell, TRUE);
	}
	$vars['header'] = $header;
}

function cmwn_tablesort_header($cell, $header, $ts) {
	// Special formatting for the currently sorted column header.
	if (is_array($cell) && isset($cell['field'])) {
		$title = t('sort by @s', array('@s' => $cell['data']));
		if ($cell['data'] == $ts['name']) {
			$ts['sort'] = (($ts['sort'] == 'asc') ? 'desc' : 'asc');
			if (isset($cell['class'])) {
				$cell['class'] .= ' active';
			}
			else {
				$cell['class'] = 'active';
			}
			$image = theme('tablesort_indicator', $ts['sort']);
		}
		else {
			// If the user clicks a different header, we want to sort ascending initially.
			$ts['sort'] = 'asc';
			$image = '';
		}

		if (!empty($ts['query_string'])) {
			$ts['query_string'] = '&'. $ts['query_string'];
		}
		$cell['data'] = l(($cell['data'] == 'Topic' ? 'Post Title' : $cell['data']) . $image, $_GET['q'], array('attributes' => array('title' => $title), 'query' => 'sort='. $ts['sort'] .'&order='. urlencode($cell['data']) . $ts['query_string'], 'html' => TRUE));

		unset($cell['field'], $cell['sort']);
	}
	return $cell;
}

function cmwn_node_submitted($node) {
	return t('@datetime by !username',
		array(
		'!username' => theme('username', $node),
		'@datetime' => format_date($node->created, 'custom', variable_get('date_format_forum', '')),
	));
}

function cmwn_comment_submitted($comment) {
	return t('@datetime by !username',
		array(
		'!username' => theme('username', $comment),
		'@datetime' => format_date($comment->timestamp, 'custom', variable_get('date_format_forum', '')),
	));
}
