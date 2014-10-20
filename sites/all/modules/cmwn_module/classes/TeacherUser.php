<?php

class TeacherUser extends GenericUser {
  
  protected $_teacherProfile;
  
  /**
   * 
   * Enter description here ...
   * @param unknown_type $obj
   * @return TeacherUser
   */
  public static function castAs($obj) {
    if ($obj instanceof TeacherUser) {
      return $obj;
    }
    try {
      $obj = new TeacherUser($obj);
      return $obj;
    } catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
      return false;
    }
  }
  
  public static function canHydrate($obj) {
    return isset($obj->roles) && is_array($obj->roles) && in_array(get_role_from_rid(variable_get('cmwn_module_teacher_role', '')), $obj->roles);
  }
  
  public function __construct($obj) {
    if (!self::canHydrate($obj)) {
      throw new Exception('Unable to cast as TeacherUser');
    }
    parent::__construct($obj);
    $this->_teacherProfile = content_profile_load('teacher_profile', $this->uid);
  }
  
}