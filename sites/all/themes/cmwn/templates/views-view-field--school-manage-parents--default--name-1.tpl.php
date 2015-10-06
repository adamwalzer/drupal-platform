<?php
//this file lists all the parent's chidlren
$children = v2_profiles_get_children_by_parent_uid($row->uid);
print implode(', ',  $children);
?>