Chức Năng của Các Tham Số

    dir: Thư mục cha nơi tệp đặc biệt mới sẽ được tạo ra. Hầu hết các trình điều khiển sẽ sử dụng NULL để tạo các tệp đặc biệt trực tiếp trong /dev. Để tạo một thư mục sở hữu, trình điều khiển cần gọi devfs_mk_dir.
    name: Tên của thiết bị, không có /dev/ dẫn đầu. Tên này có thể bao gồm dấu gạch chéo nếu bạn muốn thiết bị nằm trong một thư mục con.
    flags: Một mặt nạ bit của các cờ devfs. DEVFS_FL_DEFAULT là một lựa chọn tốt và DEVFS_FL_AUTO_DEVNUM là cờ cần thiết để tự động gán các số chính và phụ.
    major và minor: Số chính và phụ của thiết bị. Không sử dụng nếu DEVFS_FL_AUTO_DEVNUM được chỉ định trong các cờ.
    mode: Chế độ truy cập của thiết bị mới.
    ops: Một con trỏ đến cấu trúc hoạt động tệp cho thiết bị.
    info: Giá trị mặc định cho filp->private_data. Hệ thống tập tin sẽ khởi tạo con trỏ này với giá trị này khi thiết bị được mở.

Cờ devfs

    DEVFS_FL_NONE: Đơn giản là 0, đề xuất để dễ đọc mã.
    DEVFS_FL_DEFAULT: Hiện tại được định nghĩa là DEVFS_FL_NONE, nhưng là một lựa chọn tốt để tương thích với các triển khai tương lai.
    DEVFS_FL_AUTO_OWNER: Thiết bị sẽ xuất hiện là thuộc về uid/gid cuối cùng mở nó và có quyền đọc/ghi cho bất kỳ ai khi không có quá trình nào mở nó. Hữu ích cho các tệp thiết bị tty và ngăn truy cập đồng thời vào thiết bị không chia sẻ.
    DEVFS_FL_SHOW_UNREG: Yêu cầu không loại bỏ tệp thiết bị khỏi /dev khi nó bị hủy đăng ký.
    DEVFS_FL_HIDE: Yêu cầu không bao giờ hiển thị trong /dev.
    DEVFS_FL_AUTO_DEVNUM: Tự động cấp phát số thiết bị cho thiết bị này và giữ số này ngay cả khi mục devfs bị hủy đăng ký.
    DEVFS_FL_NO_PERSISTENCE: Không theo dõi mục này sau khi nó bị loại bỏ, tiết kiệm bộ nhớ hệ thống sau khi loại bỏ mô-đun.
