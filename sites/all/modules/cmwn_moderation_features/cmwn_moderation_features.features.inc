<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function cmwn_moderation_features_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}

/**
 * Implementation of hook_views_api().
 */
function cmwn_moderation_features_views_api() {
  return array(
    'api' => '2',
  );
}
