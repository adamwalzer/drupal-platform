<?php

/**
 * Expose themes as context reactions.
 */
class context_reaction_page_title extends context_reaction {

  /**
   * Allow admins to choose the theme to be set.
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form = array(
      '#tree' => TRUE,
      '#title' => t('Page Title'),
      'page_title' => array(
        '#title' => t('Page Title'),
        '#description' => t('Set the page title.'),
        '#type' => 'textfield',
        '#default_value' => isset($values['page_title']) ? $values['page_title'] : '',
      ),
    );
    return $form;
  }

  /**
   * Set the active theme.
   */
  function execute() {
	drupal_set_title();
    foreach (context_active_contexts() as $context) {
      if (!empty($context->reactions[$this->plugin]['page_title'])) {
        drupal_set_title($context->reactions[$this->plugin]['page_title']);
      }
    }
  }
}