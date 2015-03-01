<?php

function cmwn_theme(&$existing, $type, $theme, $path) {
  // Keep track of all the base themes.
  static $base_themes = array();
  $base_themes[] = $theme;

  // Add a "process" phase to come after the "preprocess" functions.
  if ($type == 'theme') {
    foreach (array_keys($existing) as $hook) {
      // Normally, preprocess functions are added to the registry after
      // HOOK_theme() returns, but if we add them first, they won't be re-added.
      if (function_exists($theme . '_preprocess')) {
        $existing[$hook]['preprocess functions'][] = $theme . '_preprocess';
      }
      if (function_exists($theme . '_preprocess_' . $hook)) {
        $existing[$hook]['preprocess functions'][] = $theme . '_preprocess_' . $hook;
      }
      // Add base theme process functions.
      foreach ($base_themes as $base_theme) {
        if (function_exists($base_theme . '_process')) {
          $existing[$hook]['preprocess functions'][] = $base_theme . '_process';
        }
        if (function_exists($base_theme . '_process_' . $hook)) {
          $existing[$hook]['preprocess functions'][] = $base_theme . '_process_' . $hook;
        }
      }
      // Add the theme process functions.
      if (function_exists($theme . '_process')) {
        $existing[$hook]['preprocess functions'][] = $theme . '_process';
      }
      if (function_exists($theme . '_process_' . $hook)) {
        $existing[$hook]['preprocess functions'][] = $theme . '_process_' . $hook;
      }
    }
  }

  // Manipulations only to be done by the base theme.
  if ($theme == 'cmwn') {
    // Allow theme hook suggestions on theme_links.
    $existing['links']['pattern'] = 'links__';

    // The base theme registers region.tpl.php.
    $templates = array(
      'cmwn_primary_links' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'primary_links',
        'include files' => array()
      ),
      'user-register-child-step2-reminder' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'user-register-child-step2-reminder',
        'include files' => array()
      ),
      'user-register-parent-step1-reminder' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'user-register-parent-step1-reminder',
        'include files' => array()
      ),
      'user-register-account-exists' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'user-register-account-exists',
        'include files' => array()
      ),
      'cmwn_parent_reminder_overlay' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'cmwn_parent_reminder_overlay',
        'include files' => array()
      ),
      'cmwn_parent_child_perms_reminder_overlay' => array(
        'arguments' => array(),
        'path' => drupal_get_path('theme', 'cmwn').'/templates',
        'template' => 'cmwn_parent_child_perms_reminder_overlay',
        'include files' => array()
      )
    );
    // We have to manually find template suggestions since phptemplate_theme()
    // is in charge of that, but runs before zen_theme().
    $templates += drupal_find_theme_templates($templates, '.tpl.php', $path);
    // We manually register the preprocess and process functions, since Drupal
    // won't auto-register template_preprocess or process functions.
    foreach (array_keys($templates) as $key) {
      $templates[$key]['preprocess functions'] = array(
        'template_preprocess',
        'cmwn_preprocess',
        'cmwn_process',
      );
    }
    return $templates;
  }

  // Else return nothing.
  return array();
}

function cmwn_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }
  $link['title'] = $link['localized_options']['html'] ? $link['title'] : check_plain($link['title']);
  $link['localized_options']['html'] = true;

  return l('<span>'.$link['title'].'</span>', $link['href'], $link['localized_options']);
}

function cmwn_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
  if (!empty($extra_class)) {
    $class .= ' '. $extra_class;
  }
  if ($in_active_trail) {
    $class .= ' active-trail';
  }
  $classes = explode(' ', $extra_class);
  $prefix = '<div class="separator"></div>';
  if (in_array('first', $classes)) {
    $prefix = '';
  }
  return '<li class="'. $class .'">'.$prefix. $link . $menu ."</li>\n";
}

function cmwn_form_element($element, $value) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  $output = '<div class="form-item"';
  if (!empty($element['#id'])) {
    $output .= ' id="' . $element['#id'] . '-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="' . $t('This field is required.') . '">*</span>' : '';

  if (!empty($element['#title'])) {
    $colon = true;
    if (isset($element['#colon'])) {
      $colon = $element['#colon'];
    }
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="' . $element['#id'] . '">' . $t('!title'.($colon ? ':' : '').' !required', array('!title' => filter_xss_admin($title), '!required' => $required)) . "</label>\n";
    }
    else {
      $output .= ' <label>' . $t('!title'.($colon ? ':' : '').' !required', array('!title' => filter_xss_admin($title), '!required' => $required)) . "</label>\n";
    }
  }

  $output .= " $value\n";

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}


function cmwn_process_html(&$variables) {
  $variables['styles'] = preg_replace('/\.css\?.*"/','.css"', $variables['styles']);
}