<?php

function cmwn_module_moderate_content() {
  $out = '';
  //$out .= views_embed_view('moderate_group_message', 'block_1');
  $out .= '<h2>Forum Topics</h2>'.views_embed_view('moderate_group_message', 'block_1');
  $out .= '<h2>Videos</h2>'.views_embed_view('moderate_video', 'block_1');
  return $out;
}

function cmwn_module_moderate_group_message() {
  return views_embed_view('moderate_group_message', 'default');
}

function cmwn_module_moderate_forum_post() {
  return views_embed_view('moderate_forum_post', 'default');
}