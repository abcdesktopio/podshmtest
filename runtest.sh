

POD_YAML=podsendershared_success.yaml
if [ ! -z "$1" ]; then
  POD_YAML=$1
fi

kubectl delete pods podsysvsendershmtest
kubectl create -f $POD_YAML 
kubectl wait pods podsysvsendershmtest  --for condition=Ready --timeout=90s

echo "**** Start sender ****"
kubectl exec -it pod/podsysvsendershmtest -c sender -- /src/sysv/sender.sh

echo "**** Read on receiver **** "
kubectl exec -it pod/podsysvsendershmtest -c receiver -- /src/sysv/receiver.sh

