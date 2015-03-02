<?php

$v2_profiles_theme_items['v2_profiles_resource_center_index'] = array(
	'arguments' => array('data' => array()),
	'template' => 'templates/resource_center/index'
);

function v2_profiles_resource_query_all($uid) {

	$items = array();

	$u = user_load($uid);

	if (!$u) return $items;

	$query = "
		SELECT
			n.nid
		FROM
			`node` AS `n`
		WHERE
			`n`.`type` = 'resource' AND
			`n`.`status` = 1
		ORDER by n.created desc
	";

	$results = db_query($query);

	while ($result = db_fetch_object($results)) {
		$classes = array();
		$classes[] = 'item';
		$node = node_load($result->nid);
		if($node){
  		$item = array(
  			'description'=>$node->body,
  			'href' => '/node/'.$result->nid,
  			'id'=>$result->nid,
  			'title' => $node->title,
  		);
  		$items[] = (object)$item;
		}
	}
	return $items;
}

function v2_profiles_resource_center_index() {
	$data = new stdClass();


	$user = user_load($uid);

  $view = views_get_view('resource_center');

  $data = $view->execute_display('default');
	//return theme('v2_profiles_resource_center_index', $data);
  return theme('v2_profiles_resource_center_index', theme('image', 'sites/all/themes/cmwn/assets/img/resource-center-coming-soon.jpg'));
}
