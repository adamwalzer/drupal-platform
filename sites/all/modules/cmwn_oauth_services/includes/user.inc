<?php

function cmwn_oauth_services_user($op, &$edit, &$account, $category = NULL) {

  switch($op){
    case 'insert':
    
      break;
      
    case 'load'://make these fields available in the user object.

      $result = db_query("select couc.cid, occ.name, occ.title from {cmwn_oauth_user_context} couc, {oauth_common_context} occ where couc.uid = %d and couc.cid = occ.cid", $account->uid);
      
      $items = array();
      while ($row = db_fetch_object($result)) {
        $items[$row->cid] = $row;
      }
      
      $account->cmwn_oauth_user_context = $items;
      break;
      
    case 'update'://update this user's contexts
      $cids = $edit['cmwn_oauth_user_context'];
      $uid = $account->uid;
      unset($edit['cmwn_oauth_user_context']);

      if(is_array($cids)){
        foreach($cids as $key=>$cid){
          //drupal_set_message($key . ' => ' . $cid);
          if($cid != 0){
            if($uid > 0){
              //db_query("INSERT INTO {cmwn_oauth_user_context} (uid, cid) VALUES (%d, %d)", $uid, $cid);
              db_query("INSERT IGNORE INTO {cmwn_oauth_user_context} set uid = %d, cid = %d", $uid, $cid);
            }
          }else{
            db_query("delete from {cmwn_oauth_user_context} where  uid= %d and cid = %d", $uid, $key);
          }
        }
      }
        
      break;
    
    case 'form'://add our fields to the user form
        if($category == 'account'){

          $contexts = oauth_common_context_load_all();
          $options = array();
          
          if($contexts){
            foreach($contexts as $title => $context){
              $options[$context->cid] = $context->title;
            }
          }
          
          $defaults = array();
          
          foreach($account->cmwn_oauth_user_context as $context){
            $defaults[$context->cid] = $context->cid;
          }
          
          //dsm($defaults);
          $form['cmwn_oauth_user_context'] = array(
            '#title' => t('Application Access'),
            '#type' => 'checkboxes',
            '#options' => $options,
            '#default_value' => @$defaults,
          );
          
          return $form;          
        } 
      break;
  } 
}