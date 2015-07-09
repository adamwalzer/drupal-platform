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

  public function getTeacherProfile() {
    return $this->_teacherProfile;
  }

  public function __construct($obj) {
    if (!self::canHydrate($obj)) {
      throw new Exception('Unable to cast as TeacherUser');
    }
    parent::__construct($obj);
    $this->_teacherProfile = content_profile_load('teacher_profile', $this->uid);
  }

  public function getSchool() {
    $sql = <<<EOSQL
SELECT
	n2.nid
FROM {node} n
INNER JOIN {content_field_school} cfs ON cfs.vid = n.vid
INNER JOIN {node} n2 ON cfs.field_school_nid = n2.nid

WHERE n.uid = %d limit 1
EOSQL;
    $nid = db_result(db_query($sql, $this->uid));
    return node_load($nid);
  }
  


}
