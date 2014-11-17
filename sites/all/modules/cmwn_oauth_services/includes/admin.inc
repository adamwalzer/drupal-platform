<?php
  
  function cmwn_oauth_services_form_alter(&$form, &$form_state, $form_id) {

    switch($form_id){
      case 'oauth_common_form_consumer':
        $ip_default =db_result(db_query("select ip from {oauth_common_provider_consumer} where csid = '%d'",@$form['consumer_object']['#value']->csid));
        $form['ip'] = array(
          '#type' => 'textfield',
          '#maxlength' => 30,
          '#default_value' => $ip_default?$ip_default:NULL,
          '#title' => t('Restrict access to only requests from this IP Address'),
          '#weight' => 1,
        );
        
        $domain_default =db_result(db_query("select domain from {oauth_common_provider_consumer} where csid = '%d'",@$form['consumer_object']['#value']->csid));        
        $form['domain'] = array(
          '#type' => 'textfield',
          '#maxlength' => 50,
          '#default_value' => $domain_default?$domain_default:NULL,
          '#title' => t('Restrict access to only requests from this Domain'),
          '#weight' => 2,
        );        
        $form['submit']['#weight'] = 3;
        $form['#submit'] = array('cmwn_oauth_services_oauth_common_form_consumer_submit');//note we are replacing the submit function provided by oauth_common_consumers.inc, not adding a secondary submit function to run subsequent to the default submit function.
        
        break;
      default:
        break;
    }
  }
  
  
  function cmwn_oauth_services_oauth_common_form_consumer_submit($form, &$form_state) {//replaces oauth_common_form_consumer_submit default submit function
    $values = $form_state['values'];
    $consumer = $values['consumer_object'];
  
    // Translate empty callback url to oob (out of band).
    if (empty($values['callback_url'])) {
      $values['callback_url'] = 'oob';
    }
    // Add scheme if missing, and if the callback_url isn't out of band.
    else if ($values['callback_url'] != 'oob' && preg_match('/^http:\/\/|https:\/\//', $values['callback_url']) === 0) {
      //TODO: What about custom callback url:s used by eg iphone-apps? We should allow them - right?
      $values['callback_url'] = 'http://' . $values['callback_url'];
    }
  
    // Remove trailing slash
    $values['callback_url'] = rtrim($values['callback_url'], '/');
  
    // Transfer editable attributes to the consumer.
    $names = array('name', 'callback_url', 'context', 'ip', 'domain');//lwd added ip and domain as extra fields
    foreach ($names as $name) {
      if (isset($values[$name])) {
        $consumer->$name = $values[$name];
      }
    }
  
    // Update or create the consumer.
    $update = $consumer->in_database;
    $consumer->write();
  
    if ($update) {
      drupal_set_message(t('Updated the consumer @name', array('@name' => $values['name'])));
    }
    else {
      drupal_set_message(t('Added the consumer @name', array('@name' => $values['name'])));
    }
  
    drupal_goto(sprintf('user/%d/oauth/consumers', $consumer->uid));
  }  
  
  //note, this hook does not change any structure, it simply reports it to other modules so they know we've changed their table
  function cmwn_oauth_services_schema_alter(&$schema) {
    // Add field to existing schema.
    $schema['oauth_common_provider_consumer']['fields']['ip'] = array(
      'type' => 'varchar',
      'description' => "Holds ip address request must come from",
      'length' => 30,
      'not null' => FALSE,
    ); 
  
    $schema['oauth_common_provider_consumer']['fields']['domain'] = array(
      'type' => 'varchar',
      'description' => "Hold domain request must come from",
      'length' => 50,
      'not null' => FALSE,
    );   
}  