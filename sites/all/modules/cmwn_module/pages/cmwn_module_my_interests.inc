<?php

function cmwn_module_my_interests($node = null) {
  global $user;
  if ($node) {
    echo '<h2>'.$node->title.'</h2>'.views_embed_view('brand_partner_videos', 'default', $node->nid);
    exit;
  } else {
    $interests = array();
    if (ChildUser::canHydrate($user)) {
      $child = ChildUser::castAs($user);
      $interests = $child->getInterests();
      /*foreach ($interests as $interest) {
        
      }*/
    } else {
      $sql = "SELECT nid FROM {node} WHERE type = 'interest'";
      $result = db_query($sql);
      while ($row = db_fetch_object($result)) {
        $interests[] = $row;
      }
    }
    return theme('cmwn_module_my_interests', $user, $interests);
  }
}