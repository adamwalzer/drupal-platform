<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function cmwn_moderation_features_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'moderation_dashboard';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'mod' => 'mod',
        'mod*' => 'mod*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-moderation' => array(
          'module' => 'menu',
          'delta' => 'menu-moderation',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => 1,
          'region' => 'content_top',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['moderation_dashboard'] = $context;

  return $export;
}
