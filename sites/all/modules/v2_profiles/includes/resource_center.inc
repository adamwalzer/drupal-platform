<?php

	$v2_profiles_menu_items["user/%/resources"] = array(
		"access arguments" => array(1),
		"access callback" => 'v2_profiles_access',
		"description" => "",
		"page arguments" => array(1),
		"page callback" => "v2_profiles_resource_center_index",
		"title" => "News",
		"type" => MENU_CALLBACK,
	);


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

function v2_profiles_resource_center_index($uid,$type = 'parent') {
	$data = new stdClass();

	$user = user_load($uid);

  $view = views_get_view('resource_center');

  $data = $view->execute_display('default');
	//return theme('v2_profiles_resource_center_index', $data);
	$partners = v2_profiles_partners_index($uid);
	if($type == 'parent'){
    $resource = theme('v2_profiles_resource_center_index', $user);
	}elseif($type == 'teacher'){
    $resource = theme('v2_profiles_resource_center_index', $user);
	}

  if(arg(2) == 'resources'){
    return $resource . $partners;
  }else{
    return $resource;
  }
}