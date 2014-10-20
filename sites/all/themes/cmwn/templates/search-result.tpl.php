<?php

/**
 * @file search-result.tpl.php
 * Default theme implementation for displaying a single search result.
 *
 * This template renders a single search result and is collected into
 * search-results.tpl.php. This and the parent template are
 * dependent to one another sharing the markup for definition lists.
 *
 * Available variables:
 * - $url: URL of the result.
 * - $title: Title of the result.
 * - $snippet: A small preview of the result. Does not apply to user searches.
 * - $info: String of all the meta information ready for print. Does not apply
 *   to user searches.
 * - $info_split: Contains same data as $info, split into a keyed array.
 * - $type: The type of search, e.g., "node" or "user".
 *
 * Default keys within $info_split:
 * - $info_split['type']: Node type.
 * - $info_split['user']: Author of the node linked to users profile. Depends
 *   on permission.
 * - $info_split['date']: Last update of the node. Short formatted.
 * - $info_split['comment']: Number of comments output as "% comments", %
 *   being the count. Depends on comment.module.
 * - $info_split['upload']: Number of attachments output as "% attachments", %
 *   being the count. Depends on upload.module.
 *
 * Since $info_split is keyed, a direct print of the item is possible.
 * This array does not apply to user searches so it is recommended to check
 * for their existance before printing. The default keys of 'type', 'user' and
 * 'date' always exist for node searches. Modules may provide other data.
 *
 *   <?php if (isset($info_split['comment'])) : ?>
 *     <span class="info-comment">
 *       <?php print $info_split['comment']; ?>
 *     </span>
 *   <?php endif; ?>
 *
 * To check for all available data within $info_split, use the code below.
 *
 *   <?php print '<pre>'. check_plain(print_r($info_split, 1)) .'</pre>'; ?>
 *
 * @see template_preprocess_search_result()
 */
?>
<?php
/*$target = '';
if ($result['node']) {
  switch ($result['node']->type) {
    case 'news':
      $node = node_load($result['node']->nid);
      if ($node->field_link[0]['url']) {
        $url = $node->field_link[0]['url'];
        $target = $node->field_link[0]['attributes']['target'];
      }
      break;
    case 'resource':
      $node = node_load($result['node']->nid);
      $media_type = $node->field_resource_mediatype[0]['value'];
      if ($media_type) {
        switch ($media_type) {
          case '126': // News
            $url = url('about/news');
            break;
          case '131': // Press Release
            //$url = url('about/news/press-releases');
            break;
          case '13': // White Paper
            $url = url($node->field_resource_file[0]['filepath']);
            break;
          case '15': // Webcast
            $url = url('resources/webcasts');
            print '<pre>';var_dump($node);print '</pre>';
            break;
          case '14': // E-book
            $url = url($node->field_resource_file[0]['filepath']);
            break;
          case '12': // Case Study
            $url = url($node->field_resource_file[0]['filepath']);
            break;
          case '16': // Demo
            //$url = url('resources/demos');
            break;
          case '17': // Video
            break;
        }
      }
      break;
    case 'video':
      $node = node_load($result['node']->nid);
      $width = $node->field_video_width[0]['value'] ? $node->field_video_width[0]['value'] : 640;
      $height = $node->field_video_width[0]['value'] ? $node->field_video_width[0]['value'] : 385;
      if (isIpad()) {
        $url = url('node/' . $node->nid);
      } else {
        $url = 'javascript:openVideo(\'/' . drupal_get_path_alias('node/' . $node->nid) . '\', ' . $width . ', ' . $height . ')';
      }
      //print '<pre>';var_dump($node);print '</pre>';
      //$url = url('resources/videos');
      break;
  }
}*/
?>
<dt class="title">
  <a href="<?php print $url; ?>"<?php if ($target) print ' target="'.$target.'"';?>><?php print $title; ?></a>
</dt>
<dd>
  <?php if ($snippet) : ?>
    <p class="search-snippet"><?php print $snippet; ?></p>
  <?php endif; ?>
</dd>
