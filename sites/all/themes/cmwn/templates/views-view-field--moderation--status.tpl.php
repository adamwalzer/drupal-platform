<?php
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */

$flags = flag_get_content_flags('node', $row->nid);
$flag_type = array();
if(is_array($flags)){
  foreach($flags as $flag){
    if(is_array($flag) && count($flag) > 0){
    foreach($flag as $flag_name => $flag_data){
        if(!isset($flag_type[$flag_name])){
          $flag_type[$flag_name] = 1;
        }else{
          $flag_type[$flag_name]++;        
        }
      }
    }
  }  
}

foreach($flag_type as $flag=>$count){
  print '<span class="mod-' . $flag . '">' . $count . '</span>';
}
?>
<?php print $output; ?>