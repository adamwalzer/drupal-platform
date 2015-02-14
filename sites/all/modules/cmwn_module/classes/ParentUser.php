<?php

class ParentUser extends GenericUser {
  
  protected $_parentProfile;
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return ParentUser
   */
  public static function castAs($obj) {
    if ($obj instanceof ParentUser) {
      return $obj;
    }
    try {
      $obj = new ParentUser($obj);
      return $obj;
    } catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
      return false;
    }
  }
  
  public static function canHydrate($obj) {
    return isset($obj->roles) && is_array($obj->roles) && in_array(get_role_from_rid(variable_get('cmwn_module_parent_role', '')), $obj->roles);
  }
  
  public function __construct($obj) {
    if (!self::canHydrate($obj)) {
      throw new Exception('Unable to cast object as ParentUser.');
    }
    parent::__construct($obj);
    $this->_parentProfile = content_profile_load('parent_profile', $this->uid);
  }
  
  public function getParentProfile() {
    return $this->_parentProfile;
  }
  
  /**
   * @return array ChildUser
   * Enter description here ...
   */
  public function getChildren() {
    $relationships = user_relationships_load(array('user' => $this->uid, 'name' => 'parent'));
    //var_dump($relationships);die;
    $children = array();
    foreach ($relationships as $relationship) {
      if ($relationship->rtid == 2 && $relationship->approved) {
        $child = ChildUser::castAs(user_load($relationship->requestee_id));
        $children[$child->uid] = $child;
      }
    }
    return $children;
  }
  
}