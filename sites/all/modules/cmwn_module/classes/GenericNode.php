<?php

class GenericNode {
  
  protected $_baseProfile;
  
  public function __construct($obj) {
    foreach (get_object_vars($obj) as $key => $val) {
      $this->{$key} = $val;
    }
    $this->_baseProfile = content_profile_load('base_profile', $this->uid);
  }
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return GenericNode
   */
  public static function castAs($obj) {
    if ($obj instanceof GenericNode) {
      return $obj;
    }
    return new GenericNode($obj);
  }
  
}