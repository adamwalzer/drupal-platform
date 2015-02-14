<?php

function cmwn_module_sponsor_logo_node_form(&$form, &$form_state) {
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
}

function cmwn_module_hum_news_node_form(&$form, &$form_state) {
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
}

function cmwn_module_school_node_form(&$form, &$form_state) {
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
}

function cmwn_module_video_node_form(&$form, &$form_state) {
  //var_dump($form);die;
  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['field_school']['#access'] = false;
  }
  if ($nid = intval($_GET['school'])) {
    if ($school = node_load($nid)) {
      if (ChildUser::canHydrate($user)) {
        $child = ChildUser::castAs($user);
        $childSchool = $child->getSchool();
        if ($school && $school->nid == $childSchool->nid) {
          $form['field_school']['#default_value'] = array('nid' => $school->nid);
          $form['field_school']['#value'] = array('nid' => $school->nid);
        }
      }
    }
  }
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
  if (!user_access('moderate_viddler_videos')) {
    $form['field_viddler_id']['#access'] = false;
    $form['field_viddler_permalink']['#access'] = false;
    $form['field_viddler_thumbnail']['#access'] = false;
  }
}

function cmwn_module_project_submission_node_form(&$form, &$form_state) {
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
  $project = node_load(arg(1));
  if ($project && $project->type == 'project') {
    $form['title']['#access'] = false;
    $form['title']['#value'] = 'testing';
    $form['og_nodeapi']['visible']['og_groups']['#access'] = false;
    $form['og_nodeapi']['visible']['og_groups']['#value'] = array($project->nid);
  }
}

function cmwn_module_project_submission_node_form_submit($form, &$form_state) {
  
}

function cmwn_module_badge_node_form(&$form, &$form_state) {
  $form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;
}

function cmwn_module_forum_node_form(&$form, &$form_state) {
  global $user;
  //var_dump($form);die;
  /*if (!in_array('administrator', $user->roles)) {
    $form['taxonomy']['#type'] = 'value';
  }*/
  /*$form['menu']['#access'] = false;
  $form['path']['#access'] = false;
  $form['comment_settings']['#access'] = false;
  $form['revision_information']['#access'] = false;
  $form['buttons']['preview']['#access'] = false;
  $form['options']['promote']['#access'] = false;
  $form['options']['sticky']['#access'] = false;*/
}