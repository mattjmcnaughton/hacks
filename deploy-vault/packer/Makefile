lint:
	shellcheck install.sh
	shellcheck base.sh
	packer validate packer.json

test:
	packer build -only=vagrant packer.json

build:
	packer build -only=amazon-ebs packer.json

clean:
	rm -rf output-vagrant
	rm ubuntu-bionic-18.04-cloudimg-console.log
