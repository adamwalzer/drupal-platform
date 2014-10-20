<?php

function cmwn_module_child_permission_form($form_state, $child) {
  $roles = user_roles();
  $form = array(
    'upload_video' => array(
      '#type' => 'checkbox',
      '#title' => 'Can Upload Video',
      '#default_value' => in_array($roles[variable_get('cmwn_child_perms_roles_upload_video', '')], $child->roles),
    ),
    'upload_pictures' => array(
      '#type' => 'checkbox',
      '#title' => 'Can Upload Pictures',
      '#default_value' => in_array($roles[variable_get('cmwn_child_perms_roles_upload_pictures', '')], $child->roles),
    ),
    'make_friends' => array(
      '#type' => 'checkbox',
      '#title' => 'Can Make Friends',
      '#default_value' => in_array($roles[variable_get('cmwn_child_perms_roles_make_friends', '')], $child->roles),
    ),
    'child' => array(
      '#type' => 'value',
      '#value' => $child
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => 'Save',
    ),
  );
  return $form;
}

function cmwn_module_child_permission_form_submit($form, &$form_state) {
  $child = $form_state['values']['child'];
  $roles = user_roles();
  $add_roles = array();
  $remove_roles = array();
  $rid_upload_video = variable_get('cmwn_child_perms_roles_upload_video', '');
  $rid_upload_pictures = variable_get('cmwn_child_perms_roles_upload_pictures', '');
  $rid_make_friends = variable_get('cmwn_child_perms_roles_make_friends', '');
  if ($child) {
    if ($form_state['values']['upload_video']) {
      $add_roles[$rid_upload_video] = $roles[$rid_upload_video];
    } else {
      $remove_roles[$rid_upload_video] = $roles[$rid_upload_video];
    }
    if ($form_state['values']['upload_pictures']) {
      $add_roles[$rid_upload_pictures] = $roles[$rid_upload_pictures];
    } else {
      $remove_roles[$rid_upload_pictures] = $roles[$rid_upload_pictures];
    }
    if ($form_state['values']['make_friends']) {
      $add_roles[$rid_make_friends] = $roles[$rid_make_friends];
    } else {
      $remove_roles[$rid_make_friends] = $roles[$rid_make_friends];
    }
    $changed = false;
    foreach ($add_roles as $rid => $role) {
      $child->roles[$rid] = $role;
      $changed = true;
    }
    foreach ($remove_roles as $rid => $role) {
      if (in_array($role, $child->roles)) {
        unset($child->roles[$rid]);
        $changed = true;
      }
    }
    if ($changed) {
      user_save($child, array('roles' => $child->roles));
    }
    drupal_set_message('Saved changes');
    drupal_goto('user');
  }
}