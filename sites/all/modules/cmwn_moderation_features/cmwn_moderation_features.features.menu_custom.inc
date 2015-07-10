<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function cmwn_moderation_features_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-moderation
  $menus['menu-moderation'] = array(
    'menu_name' => 'menu-moderation',
    'title' => 'Moderation Menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Moderation Menu');


  return $menus;
}
