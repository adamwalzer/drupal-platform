<?php

function cmwn_process(&$vars, $hook) {
  // Don't clobber Views 3 classes.
  if (array_key_exists('classes_array', $vars) && !array_key_exists('classes', $vars)) {
    $vars['classes'] = implode(' ', $vars['classes_array']);
  }
}

function cmwn_process_block(&$vars, $hook) {
  
}