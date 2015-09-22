<?php

	/* 1.4 */

	$v2_profiles_menu_items["user/%/flips"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_flips_index",
		"title" => "Flips",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/flips/%"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1,3),
		"page callback" => "v2_profiles_flips_read",
		"title" => "Flips",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_menu_items["user/%/flips/browse"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_flips_browse",
		"title" => "Flips",
		"type" => MENU_CALLBACK,
	);

	$v2_profiles_theme_items['v2_profiles_flips_browse'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/flips/browse'
	);

	$v2_profiles_theme_items['v2_profiles_flips_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/flips/index'
	);

	$v2_profiles_theme_items['v2_profiles_flips_partner'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/flips/partner'
	);

	$v2_profiles_theme_items['v2_profiles_flips_read'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/flips/read'
	);

	function v2_profiles_flips_browse($uid) {

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
			$interest->href = '#';
			$interest->id = $term->tid;
			$interest->title = $term->name;
			$interests[] = $interest;
		}

		$items = v2_profiles_flips_query_all($uid);

		$data->interests = $interests;
		$data->items = $items;

		return theme('v2_profiles_flips_browse', $data);

	}

	function v2_profiles_flips_index($uid) {

		$data = new stdClass();
    $data->user->uid = $uid;
		$user = user_load($uid);

		$all = v2_profiles_flips_query_all($uid);
		$new = $all;
		$completed = array();
		$started = array();

		foreach ($all as $key => $value) {
			if ($value->progress > 0) {
				unset($new[$key]);
				if ($value->progress == 100) $completed[] = $value;
				else if ($value->progress > 0) $started[] = $value;
			}
		}

		$data->items->all = $all;
		$data->items->completed = $completed;
		$data->items->new = $new;
		$data->items->started = $started;
		$data->user = $user;
		

		return theme('v2_profiles_flips_index', $data);

	}

	function v2_profiles_flips_partner($nid) {

		global $user;

		$data = new stdClass();

		$items = v2_profiles_flips_query_all($user->uid);

		foreach ($items as $key => $item) {
			$node = node_load($item->id);
			if ($node->field_brand_partner[0]['nid'] !== $nid) {
				unset($items[$key]);
			}
		}

		$data->items = $items;

		return theme('v2_profiles_flips_partner', $data);

	}

	function v2_profiles_flips_query_all($uid) {

		$items = array();

		$u = user_load($uid);

		if (!$u) return $items;

		$query = "
			SELECT
				`n`.`nid`,
				(SELECT GROUP_CONCAT(`tn`.`tid`) FROM `term_node` AS `tn` WHERE `tn`.`nid` = `n`.`nid`) AS `tids`,
				`n`.`title`,
				`nr`.`body` AS `description`,
				`ctf`.`field_color_value` AS `color`,
				`f1`.`filepath` AS `icon`,
				`f2`.`filepath` AS `icon_color`,
				`f3`.`filepath` AS `large_icon`,
				`f4`.`filepath` AS `large_icon_color`,
				COUNT(`ws`.`sid`) AS `submitted`,
				(SELECT COUNT(*) FROM `content_field_actions` AS `cfa` WHERE `cfa`.`nid` = `n`.`nid`) AS `total`,
				f5.filepath as thumbnail
			FROM
				`node` AS `n` LEFT JOIN
				`node_revisions` AS `nr` ON `n`.`vid` = `nr`.`vid` JOIN
				`content_type_flip` AS `ctf` ON `n`.`nid` = `ctf`.`nid` JOIN
				`content_field_icon` AS `cfi` ON `n`.`nid` = `cfi`.`nid` JOIN
				`files` AS `f1` ON `cfi`.`field_icon_fid` = `f1`.`fid` JOIN
				`files` AS `f2` ON `ctf`.`field_icon_color_fid` = `f2`.`fid` LEFT JOIN
				`files` AS `f3` ON `ctf`.`field_large_icon_fid` = `f3`.`fid` LEFT JOIN
				`files` AS `f4` ON `ctf`.`field_large_icon_color_fid` = `f4`.`fid` LEFT JOIN
				files as f5 ON ctf.field_thumbnail_fid = f5.fid LEFT JOIN
				`webform_submissions` AS `ws` ON `ws`.`nid` IN (SELECT `cfa`.`field_actions_nid` FROM `content_field_actions` AS `cfa` WHERE `cfa`.`nid` = `n`.`nid`) AND `ws`.`uid` = ".$u->uid."
			WHERE
				`n`.`type` = 'flip' AND
				`n`.`status` = 1
			GROUP BY
				`n`.`nid` order by RAND();
		";

		$results = db_query($query);

		while ($result = db_fetch_object($results)) {
			$classes = array();
			$classes[] = 'item';
			$tids = explode(',',$result->tids);
			foreach ($tids as $tid) {
				$classes[] = 'tid-'.$tid;
			}
			$item = array(
				'class'=>implode($classes,' '),
				'color'=>$result->color,
				'description'=>$result->description,
				'href' => '/user/'.$u->uid.'/flips/'.$result->nid,
				'id'=>$result->nid,
				'progress' => intval(($result->submitted/$result->total)*100),
				'src1' => '/'.$result->icon,
				'src2' => '/'.$result->icon_color,
				'large_src1' => '/'.$result->large_icon,
				'large_src2' => '/'.$result->large_icon_color,
				'thumbnail' => '/'.$result->thumbnail,
				'title' => $result->title,
			);
			$items[] = (object)$item;
		}

		return $items;

	}

	function v2_profiles_flips_read($uid,$nid) {

		$data = new stdClass();

		$user = user_load($uid);
		//$user->avatar = v2_profiles_avatars_query($user->uid);
		$node = node_load($nid);

		if (!$node) drupal_access_denied();

		/*$partner = node_load($node->field_brand_partner[0]['nid']);

		$node->color = $node->field_color[0]['value'];
		$node->completed = 1;
		$node->items = array();
		$node->logo = $node->field_logo[0]['filepath'];
		$node->partner->href = '/user/' . $user->uid . '/partners/' . $partner->nid;
		$node->partner->title = $partner->title;
		$node->new = 1;

		$_SESSION['v2_profiles_redirect'] = 'user/'.$user->uid.'/flips/'.$node->nid;

		foreach ($node->field_actions as $action) {
			$action = node_load($action['nid']);
			$item = new stdClass();
			$item->completed = (webform_get_submission_count($action->nid, $user->uid) > 0)? 1 : 0;
			$item->disabled = 1;
			$item->node = $action;
			$item->title = $action->field_title[0]['value'];
			$node->items[] = $item;
		}

		foreach ($node->items as $key => $item) {
			if ($item->completed == 0) {
				$node->completed = 0;
				$node->items[$key]->disabled = 0;
				break;
			} else {
				$node->items[$key]->disabled = 0;
			}
		}

		foreach ($node->items as $key => $item) {
			if ($item->completed == 1) {
				$node->new = 0;
				break;
			}
		}*/

		$data->node = $node;
		$data->user = $user;

		return theme('v2_profiles_flips_read', $data);

	}
