<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function cmwn_moderation_features_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-moderation:<front>
  $menu_links['menu-moderation:<front>'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'My Timecards',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '2',
  );
  // Exported menu link: menu-moderation:mod
  $menu_links['menu-moderation:mod'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => 'mod',
    'router_path' => 'mod',
    'link_title' => 'Moderation Feed',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-moderation:mod/approved
  $menu_links['menu-moderation:mod/approved'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => 'mod/approved',
    'router_path' => 'mod/approved',
    'link_title' => 'Approved Posts',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '1',
    'parent_path' => 'mod',
  );
  // Exported menu link: menu-moderation:mod/comments
  $menu_links['menu-moderation:mod/comments'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => 'mod/comments',
    'router_path' => 'mod/comments',
    'link_title' => 'Unmoderated Comments',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'mod',
  );
  // Exported menu link: menu-moderation:mod/denied
  $menu_links['menu-moderation:mod/denied'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => 'mod/denied',
    'router_path' => 'mod/denied',
    'link_title' => 'Denied Posts',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '2',
    'parent_path' => 'mod',
  );
  // Exported menu link: menu-moderation:user
  $menu_links['menu-moderation:user'] = array(
    'menu_name' => 'menu-moderation',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My Profile',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '1',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Approved Posts');
  t('Denied Posts');
  t('Moderation Feed');
  t('My Profile');
  t('My Timecards');
  t('Unmoderated Comments');


  return $menu_links;
}
