VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "bento/centos-7.2"
  config.vm.provision :shell, :inline =>
  "sudo yum install -y docker git mariadb \
  && sudo systemctl start docker \
  && git clone https://github.com/d9magai/docker-mod_condb.git \
  && ./docker-mod_condb/run.sh \
  && echo 'finish'
  "
end

