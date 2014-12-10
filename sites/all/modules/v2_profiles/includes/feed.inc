<?php

	/* 1.4 */

	$v2_profiles_theme_items['v2_profiles_feed_index'] = array(
		'arguments' => array('data' => array()),
		'template' => 'templates/feed/index'
	);

	function v2_profiles_feed_index($uid) {

		$data = new stdClass();

		$items = v2_profiles_feed_query_all($uid);
		$group1  = array();
		$group2  = array();
		$group3  = array();

		foreach ($items as $item) {
			if ($item->tid == 87) {
				$item->href = url('node/' . $item->nid);
				$item->src = v2_profiles_avatars_query($item->uid);
				$group1[] = $item;
			} else if ($item->tid == 88) {
				$item->href = url('node/' . $item->nid);
				$item->src = v2_profiles_avatars_query($item->uid);
				$group2[] = $item;
			} else if ($item->tid == 89) {
				$item->href = url('node/' . $item->nid);
				$item->src = v2_profiles_avatars_query($item->uid);
				$group3[] = $item;
			}
		}

		$data->items->group1 = $group1;
		$data->items->group2 = $group2;
		$data->items->group3 = $group3;

		return theme('v2_profiles_feed_index', $data);

	}

	function v2_profiles_feed_insert($uid,$tid,$title,$content,$excerpt) {

		$node = new stdClass();
		$node->body = $content;
		$node->field_excerpt[0]['value'] = $excerpt;
		$node->status = 1;
		$node->taxonomy[0]['tid'] = $tid;
		$node->title = $title;
		$node->type = 'feed';
		$node->uid = $uid;
		node_validate($node);
		node_submit($node);
		node_save($node);

	}

	function v2_profiles_feed_query_all($uid) {

		$items = array();

		$user = user_load($uid);

		if (!$user) return $items;

		$query = "
			SELECT
				`n`.`nid`,
				`n`.`uid`,
				`td`.`tid`,
				`ctf`.`field_excerpt_value` AS `excerpt`
			FROM
				`node` AS `n` JOIN
				`term_node` AS `tn` ON `n`.`nid` = `tn`.`nid` JOIN
				`term_data` AS `td` ON `tn`.`tid` = `td`.`tid` JOIN
				`content_type_feed` AS `ctf` ON `n`.`nid` = `ctf`.`nid`
			WHERE
				`n`.`type` = 'feed' AND
				`n`.`status` = 1
			ORDER BY
				`n`.`created` DESC;
		";

		$results = db_query($query,$uid);//TODO - I don't think this $uid is even filtering anything in drupal 6.x api :(

		while ($result = db_fetch_object($results)) {
			$item = new stdClass();
			$item->excerpt = $result->excerpt;
			$item->nid = $result->nid;
			$item->tid = $result->tid;
			$item->uid = $result->uid;
			$items[] = $item;
		}

		return $items;

	}