alter user 'root'@'localhost' identified with mysql_native_password by 'rootheslo';

create user 'user'@'%' identified with mysql_native_password by 'heslo';
grant all privileges on *.* to 'user'@'%' with grant option;
