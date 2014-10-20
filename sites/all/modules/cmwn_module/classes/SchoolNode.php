<?php

class SchoolNode extends GenericNode {
  
  public function __construct($obj) {
    parent::__construct($obj);
  }
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return SchoolNode
   */
  public static function castAs($obj) {
    if ($obj instanceof SchoolNode) {
      return $obj;
    }
    return new SchoolNode($obj);
  }
  
}