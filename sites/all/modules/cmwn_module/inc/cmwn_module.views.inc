<?php
/**
 * Implementation of hook_views_data_alter().
 */
function cmwn_module_views_data_alter(&$data) {
  $data['flag_content']['flagged'] = array(
    'title' => t('Is Flagged'),
    'help' => t('Is the node flagged? Yes or no.'),
    'real field' => 'timestamp',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );
}